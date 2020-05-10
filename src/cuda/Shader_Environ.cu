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
        if (i < layers.Ni && j < layers.Nj)
		{
            get_cam_normals(i, j, norm);
            *(layers.imdata + i*layers.Nj+j) = (norm[2]>0) ? settings.sky_color : settings.floor_color;
            if (settings.rdr_floor && norm[2] < 0)
            {
                int floorx, floory;
                float trav = (settings.floor_height - settings.cam_z)/(norm[2]);
                floorx = (int)floor((0.1*(trav*norm[0]+settings.cam_x)));
                floory = (int)floor((0.1*(trav*norm[1]+settings.cam_y)));
                floorx += floory;
                if ((floorx%2==0)==floorx<0) *(layers.imdata + i*layers.Nj+j) = 0x00341989;
                if (abs((0.1*(trav*norm[1]+settings.cam_y))) < 1e-2 || abs((0.1*(trav*norm[0]+settings.cam_x))) < 1e-2) *(layers.imdata + i*layers.Nj+j) = 0;
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
