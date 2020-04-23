#ifndef CUD_DAT_H
#define CUD_DAT_H
#include "Typedef.h"

namespace sharc
{
    //camera position
    extern __device__ float cam_x, cam_y, cam_z, elev_cos, elev_sin, rot_cos, rot_sin, zoom, cam_n1, cam_n2, cam_n3, screen_aspect, floor_height;
    extern __device__ bool rdr_floor;

    extern int H_skybackground, H_floorbackground;
    extern __device__ int skybackground, floorbackground;

    extern dim3 grid_conf, block_conf;
    extern int* H_imdata;

    //image data
    extern __device__ int* imdata;
    extern __device__ int i_bound, j_bound;

    ////////shader buffer layers
    //incident coordinates
    extern g_real *H_x_inc, *H_y_inc, *H_z_inc;
    extern __device__ g_real *x_inc, *y_inc, *z_inc;

    //incident normals
    extern float *H_n1_inc, *H_n2_inc, *H_n3_inc;
    extern __device__ float *n1_inc, *n2_inc, *n3_inc;

    //buffer indices
    extern uint16* H_ob_id;
    extern __device__ uint16* ob_id;

    void set_render_state(SharcSettings* settings);
    void allocate_frame_bufs(int wid, int hei);
    void free_frame_bufs(void);

}

#endif
