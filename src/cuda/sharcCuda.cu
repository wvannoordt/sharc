#include "sharcCuda.h"
#include "sharc.h"
#include "Typedef.h"
#include "CudaData.h"
#include "CudaErrorLogging.h"
#include "sharcShaders.h"
#include "Shader_TestShader.h"
#include "Shader_Environ.h"

namespace sharc
{
    void cuda_allocate_frame_buffers(void)
    {
        allocate_frame_bufs(userSettings.width, userSettings.height);
    }

    void cuda_set_render_state(void)
    {
        set_render_state(&userSettings);
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
            case SHARC_SHDR_ENVIRON:
            {
                shader_environ();
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
        free_frame_bufs();
    }
}
