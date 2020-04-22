#ifndef SHARC_CU_H
#define SHARC_CU_H

#include "sharc.h"

#define RED_SHIFT 16
#define GRN_SHIFT 8
#define BLU_SHIFT 0
#define rgb2int(red, grn, blu) ((int)(255*(red)) << RED_SHIFT) | ((int)(255*(grn)) << GRN_SHIFT) | ((int)(255*(blu)) << BLU_SHIFT)
#define int2red(myval) (ubyte)( ((myval)&(0x000000ff << RED_SHIFT)) >> RED_SHIFT)
#define int2grn(myval) (ubyte)( ((myval)&(0x000000ff << GRN_SHIFT)) >> GRN_SHIFT)
#define int2blu(myval) (ubyte)( ((myval)&(0x000000ff << BLU_SHIFT)) >> BLU_SHIFT)

namespace sharc
{
    void cuda_finalize(void);
    void cuda_allocate_frame_buffers(void);
    void cuda_compute_shader(const int shader_id);
    void offload_image_data(int* host_endpoint);
    void cuda_set_render_state(void);
}

#endif
