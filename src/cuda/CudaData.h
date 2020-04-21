#ifndef CUD_DAT_H
#define CUD_DAT_H

namespace sharc
{
    extern dim3 grid_conf, block_conf;
    extern int* H_imdata;
    extern __device__ int* imdata;
    extern __device__ int i_bound, j_bound;
}

#endif
