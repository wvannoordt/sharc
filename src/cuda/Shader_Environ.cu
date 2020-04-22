#include <iostream>
#include "CudaData.h"
#include "CudaErrorLogging.h"
#include "sharcCuda.h"
#include "Shader_Environ.h"
#include "ShaderUtils.h"
namespace sharc
{
    __global__ void K_rdr_environ_shader()
    {
        //How to best make these into macros??
        int i = blockIdx.y*blockDim.y + threadIdx.y;
		int j = blockIdx.x*blockDim.x + threadIdx.x;
        float n1, n2, n3;
        if (i < i_bound && j < j_bound)
		{
            get_cam_normals(i, j, &n1, &n2, &n3);
            *(imdata + i*j_bound+j) = (n3>0) ? skybackground : floorbackground;
		}
    }

    void shader_environ(void)
    {
        K_rdr_environ_shader<<<grid_conf, block_conf>>>();
        CU_CHK(cudaPeekAtLastError());
        CU_CHK(cudaDeviceSynchronize());
    }
}
