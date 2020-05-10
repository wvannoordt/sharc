#include <iostream>
#include "CudaData.h"
#include "CudaErrorLogging.h"
#include "sharcCuda.h"
#include "Shader_TestShader.h"
#include "CuGLInterop.h"
namespace sharc
{
    __global__ void K_rdr_test_shader()
    {
        //How to best make these into macros??
        int i = blockIdx.y*blockDim.y + threadIdx.y;
		int j = blockIdx.x*blockDim.x + threadIdx.x;
        float r,g,b;
        r = (float)((blockIdx.y + blockIdx.x)%2);
        g = 0.0;
        b = (float)((blockIdx.y/2 + blockIdx.x/2)%2);
        if (i < layers.Ni && j < layers.Nj)
		{
            *(layers.imdata + i*layers.Nj+j) = rgb2int(r, g, b);
		}
    }

    void shader_testshader(void)
    {
        K_rdr_test_shader<<<grid_conf, block_conf>>>();
        CU_CHK(cudaPeekAtLastError());
        CU_CHK(cudaDeviceSynchronize());
    }
}
