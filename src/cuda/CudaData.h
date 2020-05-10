#ifndef CUD_DAT_H
#define CUD_DAT_H
#include "Typedef.h"

namespace sharc
{
    //camera position
    extern __device__ SharcSettings settings;
    extern __device__ SharcShaderLayers layers;
    extern dim3 grid_conf, block_conf; 

    void set_render_state(SharcSettings* settings_in);
    void allocate_frame_bufs(int wid, int hei);
    void free_frame_bufs(void);

}

#endif
