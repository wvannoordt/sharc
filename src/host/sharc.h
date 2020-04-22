#ifndef SHARC_H
#define SHARC_H

#include "sharcShaders.h"
#include "ErrorCodes.h"
#include "GpuTest.h"
#include "Typedef.h"

namespace sharc
{
    extern SharcSettings userSettings;
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
    }

    void reg_error(const char* message, const char* file, const int line, const int error_code);
}

#endif
