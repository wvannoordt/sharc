#include "sharc.h"
#include "sharcCuda.h"
#include "GpuTest.h"
#include "ErrorCodes.h"
#include "PngWriter.h"
#include <iostream>
#include <cstdlib>
#include "StlGeom.h"
#include "Typedef.h"
#include "SharcUserSettingsHandle.h"
#include "SharcGL.h"

namespace sharc
{
    SharcSettings userSettings;
    SharcShaderLayers shaderLayers;
    SharcUserSettingsHandle userSettingsHandle;
    PngWriter imWriter;
    int* framebuf_host_endpoint;
    int hostArgc;
    char** hostArgv;
    GLuint pbo = 0;     // OpenGL pixel buffer object
    GLuint tex = 0;     // OpenGL texture object
    struct cudaGraphicsResource *cuda_pbo_resource;
    bool interactiveMode;
    bool finalizeCalled;

    void SHARC_Initialize(int argc, char** argv)
    {
        userSettingsHandle = SharcUserSettingsHandle(&userSettings);
        userSettingsHandle.Defaults();
        CudaSetRenderState();
        hostArgc = argc;
        hostArgv = argv;
        finalizeCalled = true;
        interactiveMode = false;
    }

    void SHARC_SetInteractiveMode(bool a)
    {
        interactiveMode = a;
    }

    void SHARC_CreateOGL(const char* title)
    {
        if (!interactiveMode) erkill(SHARC_ERR_OGL_SPEC, "SHARC_CreateOGL called in non-interactive mode: call SHARC_SetInteractiveMode(true) beforehand.");
        SharcGLInit(hostArgc, hostArgv, title);
    }

    void SHARC_AllocateFrameBuffers(void)
    {
        framebuf_host_endpoint = (int*)malloc(userSettings.width*userSettings.height*sizeof(int));
        CudaAllocateFrameBuffers();
    }

    void SHARC_SetSize(int w, int h)
    {
        userSettings.width  = w;
        userSettings.height = h;
    }

    void SHARC_OGLWindowStart(void)
    {
        SharcGLWindow();
    }

    void SHARC_SetRenderState(void)
    {
        CudaSetRenderState();
    }

    void SHARC_Offload(void)
    {
        OffloadImageData(framebuf_host_endpoint);
    }

    void SHARC_Write(std::string filename)
    {
        imWriter.WritePng(filename.c_str(), userSettings.width, userSettings.height, framebuf_host_endpoint);
    }

    void SHARC_ComputeShader(const int shader_id)
    {
        CudaComputeShader(shader_id);
    }

    void SHARC_GpuTest(void)
    {
        GpuTest();
    }

    void SHARC_Finalize(void)
    {
        if (!finalizeCalled)
        {
            finalizeCalled = true;
            free(framebuf_host_endpoint);
            CudaFinalize();
        }
    }

    void reg_error(const char* message, const char* file, const int line, const int error_code)
    {
        if (error_code != SHARC_ERR_SUCCESS)
        {
            std::cout << file << ", line " << line << ": " << message << std::endl;
            //This is temporary. There should really be a class that handles this. This is TODO.
            abort();
        }
    }
}
