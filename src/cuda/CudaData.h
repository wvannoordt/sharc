#ifndef CUD_DAT_H
#define CUD_DAT_H
#include "Typedef.h"

namespace sharc
{
    //camera position
    extern __device__ SharcSettings settings;
    extern __device__ SharcShaderLayers layers;
    extern dim3 gridConf, blockConf;

    void SetRenderState(SharcSettings* settings_in);
    void AllocateFrameBuffers(int wid, int hei);
    void FreeFrameBuffers(void);
    void OverrideOGLFrameBuffer(int* newBuf);

}

#endif
