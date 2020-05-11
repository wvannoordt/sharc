#ifndef SHARC_H
#define SHARC_H

#include "sharcShaders.h"
#include "ErrorCodes.h"
#include "GpuTest.h"
#include "Typedef.h"
#include "SharcUserSettingsHandle.h"

namespace sharc
{
    extern SharcSettings userSettings;
    extern SharcShaderLayers shaderLayers;
    extern SharcUserSettingsHandle userSettingsHandle;
    extern GLuint pbo;     // OpenGL pixel buffer object
    extern GLuint tex;     // OpenGL texture object
    extern struct cudaGraphicsResource *cuda_pbo_resource;
    extern int hostArgc;
    extern char** hostArgv;
    extern bool interactiveMode;
    extern "C"
    {
        void SHARC_Initialize(int argc, char** argv);
        void SHARC_AllocateFrameBuffers(void);
        void SHARC_ComputeShader(const int shader_id);
        void SHARC_Offload(void);
        void SHARC_Write(std::string filename);
        void SHARC_SetRenderState(void);
        void SHARC_GpuTest(void);
        void SHARC_Finalize(void);
        void SHARC_SetSize(int w, int h);
        void SHARC_SetInteractiveMode(bool a);
        void SHARC_CreateOGL(const char* title);
        void SHARC_OGLWindowStart(void);
    }
}

#endif
