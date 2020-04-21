#include "sharcCuda.h"
#include "sharc.h"
#include "Typedef.h"
#include "CudaData.h"
#include "CudaErrorLogging.h"
#include "sharcShaders.h"

namespace sharc
{
    void cuda_allocate_frame_buffers(void)
    {
        CU_CHK(cudaMalloc(&H_imdata, userSettings.width * userSettings.height * sizeof(int)));
        CU_CHK(cudaMemcpyToSymbol(imdata, &(H_imdata), sizeof(int*), 0));
        CU_CHK(cudaMemcpyToSymbol(i_bound, &(userSettings.height), sizeof(int), 0));
        CU_CHK(cudaMemcpyToSymbol(j_bound, &(userSettings.width),  sizeof(int), 0));
        int num_blocks_w = (userSettings.width  + (BLOCK_SIZE-1))/BLOCK_SIZE;
        int num_blocks_h = (userSettings.height + (BLOCK_SIZE-1))/BLOCK_SIZE;
        grid_conf =  dim3(num_blocks_w, num_blocks_h);
        block_conf = dim3(BLOCK_SIZE, BLOCK_SIZE);
    }

    void cuda_compute_shader(const int shader_id)
    {
        switch (shader_id)
        {
            case SHARC_SHDR_TEST:
            {
                shader_testshader();
                break;
            }
        }
    }

    void offload_image_data(int* host_endpoint)
    {
        CU_CHK(cudaMemcpy(host_endpoint, H_imdata, userSettings.width * userSettings.height * sizeof(int), cudaMemcpyDeviceToHost));
    }

    void cuda_finalize(void)
    {
        CU_CHK(cudaFree(H_imdata));
    }
}
