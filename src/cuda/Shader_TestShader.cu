#include <iostream>
#include "CudaData.h"
#include "CudaErrorLogging.h"
#include "sharcCuda.h"
namespace sharc
{
    __global__ void K_rdr_test_shader()
    {
        //How to best make these into macros??
        int i = blockIdx.y*blockDim.y + threadIdx.y;
		int j = blockIdx.x*blockDim.x + threadIdx.x;
        float r;
        r = (float)((blockIdx.y + blockIdx.x)%2);
        if (i < i_bound && j < j_bound)
		{
            *(imdata + i*j_bound+j) = rgb2int(r, r, r);
		}
    }

    void shader_testshader(void)
    {
        K_rdr_test_shader<<<grid_conf, block_conf>>>();
        CU_CHK(cudaDeviceSynchronize());
    }
}
