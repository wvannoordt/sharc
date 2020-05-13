#include <iostream>
#include "Config.h"
#include "GpuTest.h"
#include "CudaErrorLogging.h"
#include "sharcCuda.h"
#include "PngWriter.h"
#include "CuGLInterop.h"
namespace sharc
{
    #define FRAC_XMIN -1.25086
	#define FRAC_XMAX -1.25046
	#define FRAC_YMIN  0.02002
	#define FRAC_YMAX  0.02022
	#define FRAC_ITS 1600
	#define FRAC_RATIO 0.4
    __global__ void K_GpuTest(int* imdata, const int wid, const int hei)
    {
        int row = blockIdx.y*blockDim.y + threadIdx.y;
		int col = blockIdx.x*blockDim.x + threadIdx.x;
        if (row < hei && col < wid)
		{
			double x0 = FRAC_XMIN - (FRAC_XMIN-FRAC_XMAX)*(double)col/(double)wid;
			double y0 = FRAC_YMIN - (FRAC_YMIN-FRAC_YMAX)*(double)row/(double)hei;
			double x = x0;
			double y = y0;
			double temp;
			int ct = 0;
			bool diverged = false;
			while (ct++ < FRAC_ITS && !diverged)
			{
				temp = x*x - y*y + x0;
				y = 2*x*y + y0;
				x = temp;
				if (x*x + y*y > 4)
				{
					double ratio = (double)ct/FRAC_ITS;
					ratio = exp(0.7*log(ratio));
					double ratio_loc = 0;
					if (ratio > FRAC_RATIO)
					{
						ratio_loc = (ratio - FRAC_RATIO) / (1-FRAC_RATIO);
						ratio_loc = sqrt(ratio_loc);
                        *(imdata + row*wid + col) = rgb2int(1, sqrt(ratio_loc), ratio_loc*ratio_loc);
					}
					else
					{
						ratio_loc = ratio/FRAC_RATIO;
						ratio_loc = ratio_loc*ratio_loc;
                        *(imdata + row*wid + col) = rgb2int(ratio_loc, 0.4*(ratio_loc)*(1 - ratio_loc), 0.2*(1 - ratio_loc));
					}
					diverged = true;
				}
			}
			if (!diverged)
			{
				*(imdata + row*wid + col) = rgb2int(1, 1, 1);
			}
		}
    }

    void GpuTest(void)
    {
        int wid = SHARC_TEST_WID;
        int hei = SHARC_TEST_HEI;
        int* d_image_data;
        int* imdata = (int*)malloc(wid*hei*sizeof(int));
        CU_CHK(cudaMalloc(&d_image_data, wid*hei*sizeof(int)));

        int num_blocks_w = (wid + (BLOCK_SIZE-1))/BLOCK_SIZE;
        int num_blocks_h = (hei + (BLOCK_SIZE-1))/BLOCK_SIZE;

        dim3 grid(num_blocks_w, num_blocks_h);
        dim3 block(BLOCK_SIZE, BLOCK_SIZE);

        K_GpuTest<<<grid, block>>>(d_image_data, wid, hei);
        CU_CHK(cudaPeekAtLastError());
        CU_CHK(cudaDeviceSynchronize());
        CU_CHK(cudaMemcpy(imdata, d_image_data, wid*hei*sizeof(int), cudaMemcpyDeviceToHost));
        CU_CHK(cudaFree(d_image_data));
        PngWriter p;
        p.WritePng("fractaltest.png", wid, hei, imdata);
        free(imdata);
    }
}
