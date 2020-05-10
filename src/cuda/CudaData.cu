#include "CudaData.h"
#include "CudaErrorLogging.h"
#include "Typedef.h"
namespace sharc
{
    __device__ SharcSettings settings;
    __device__ SharcShaderLayers layers;dim3 grid_conf, block_conf;

    __global__ void K_settings(SharcSettings s)
    {
        settings = s;
    }

    __global__ void K_layers(SharcShaderLayers s)
    {
        layers = s;
    }

    void allocate_frame_bufs(int wid, int hei)
    {
        CU_CHK(cudaMalloc((void**)(&(shaderLayers.imdata)),        wid * hei * sizeof(uchar4)));
        CU_CHK(cudaMalloc((void**)(&(shaderLayers.incident_x[0])), wid * hei * sizeof(g_real)));
        CU_CHK(cudaMalloc((void**)(&(shaderLayers.incident_x[1])), wid * hei * sizeof(g_real)));
        CU_CHK(cudaMalloc((void**)(&(shaderLayers.incident_x[2])), wid * hei * sizeof(g_real)));
        CU_CHK(cudaMalloc((void**)(&(shaderLayers.incident_n[0])), wid * hei * sizeof(float)));
        CU_CHK(cudaMalloc((void**)(&(shaderLayers.incident_n[1])), wid * hei * sizeof(float)));
        CU_CHK(cudaMalloc((void**)(&(shaderLayers.incident_n[2])), wid * hei * sizeof(float)));
        CU_CHK(cudaMalloc((void**)(&(shaderLayers.object_id)),     wid * hei * sizeof(uint16)));
        shaderLayers.Nj = wid;
        shaderLayers.Ni = hei;

        int num_blocks_w = (userSettings.width  + (BLOCK_SIZE-1))/BLOCK_SIZE;
        int num_blocks_h = (userSettings.height + (BLOCK_SIZE-1))/BLOCK_SIZE;
        grid_conf =  dim3(num_blocks_w, num_blocks_h);
        block_conf = dim3(BLOCK_SIZE, BLOCK_SIZE);
        K_layers<<<1,1>>>(shaderLayers);
    }

    void free_frame_bufs(void)
    {
        CU_CHK(cudaFree(shaderLayers.imdata));
        CU_CHK(cudaFree(shaderLayers.incident_x[0]));
        CU_CHK(cudaFree(shaderLayers.incident_x[1]));
        CU_CHK(cudaFree(shaderLayers.incident_x[2]));
        CU_CHK(cudaFree(shaderLayers.incident_n[0]));
        CU_CHK(cudaFree(shaderLayers.incident_n[1]));
        CU_CHK(cudaFree(shaderLayers.incident_n[2]));
        CU_CHK(cudaFree(shaderLayers.object_id));
    }

    void set_render_state(SharcSettings* settings_in)
    {
        settings_in->elev_sin = sin(settings_in->cam_elev);
        settings_in->elev_cos = cos(settings_in->cam_elev);
        settings_in->rot_sin  = sin(settings_in->cam_rot);
        settings_in->rot_cos  = cos(settings_in->cam_rot);
        settings_in->cam_n[0] = (settings_in->elev_cos)*(settings_in->rot_cos);
        settings_in->cam_n[1] = (settings_in->elev_cos)*(settings_in->rot_sin);
        settings_in->cam_n[2] = (settings_in->elev_sin);
        K_settings<<<1,1>>>(*settings_in);
    }
}
