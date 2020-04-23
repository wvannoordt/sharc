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
        vec3 norm;
        if (i < i_bound && j < j_bound)
		{
            get_cam_normals(i, j, norm);
            *(imdata + i*j_bound+j) = (norm[2]>0) ? skybackground : floorbackground;
            if (rdr_floor && norm[2] < 0)
            {
                int floorx, floory;
                float trav = (floor_height - cam_z)/(norm[2]);
                floorx = (int)floor((0.1*(trav*norm[0]+cam_x)));
                floory = (int)floor((0.1*(trav*norm[1]+cam_y)));
                floorx += floory;
                if ((floorx%2==0)==floorx<0) *(imdata + i*j_bound+j) = 0x00341989;
                if (abs((0.1*(trav*norm[1]+cam_y))) < 1e-2 || abs((0.1*(trav*norm[0]+cam_x))) < 1e-2)*(imdata + i*j_bound+j) = 0;
            }
		}
    }

    void shader_environ(void)
    {
        K_rdr_environ_shader<<<grid_conf, block_conf>>>();
        CU_CHK(cudaPeekAtLastError());
        CU_CHK(cudaDeviceSynchronize());
    }
}
