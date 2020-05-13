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
    void CudaAllocateFrameBuffers(void)
    {
        AllocateFrameBuffers(userSettings.width, userSettings.height);
    }

    void CudaSetRenderState(void)
    {
        SetRenderState(&userSettings);
    }

    void CudaComputeShader(const int shader_id)
    {
        switch (shader_id)
        {
            case SHARC_SHDR_TEST:
            {
                Shader_TestShader();
                break;
            }
            case SHARC_SHDR_ENVIRON:
            {
                Shader_Environ();
                break;
            }
        }
    }

    void OffloadImageData(int* host_endpoint)
    {
        CU_CHK(cudaMemcpy(host_endpoint, shaderLayers.imdata, userSettings.width * userSettings.height * sizeof(int), cudaMemcpyDeviceToHost));
    }

    void CudaFinalize(void)
    {
        FreeFrameBuffers();
    }
}
