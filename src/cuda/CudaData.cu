#include "CudaData.h"
#include "CudaErrorLogging.h"
#include "Typedef.h"
namespace sharc
{
    //camera position
    __device__ float cam_x, cam_y, cam_z, elev_cos, elev_sin, rot_cos, rot_sin, zoom, cam_n1, cam_n2, cam_n3, screen_aspect;

    __device__ int skybackground, floorbackground;

    dim3 grid_conf, block_conf;
    int* H_imdata;

    //image data
    __device__ int* imdata;
    __device__ int i_bound, j_bound;

    ////////shader buffer layers
    //incident coordinates
    g_real *H_x_inc, *H_y_inc, *H_z_inc;
    __device__ g_real *x_inc, *y_inc, *z_inc;

    //incident normals
    float *H_n1_inc, *H_n2_inc, *H_n3_inc;
    __device__ float *n1_inc, *n2_inc, *n3_inc;

    //buffer indices
    uint16* H_ob_id;
    __device__ uint16* ob_id;

    void allocate_frame_bufs(int wid, int hei)
    {
        CU_CHK(cudaMemcpyToSymbol(j_bound, &(userSettings.width),  sizeof(int), 0));
        CU_CHK(cudaMemcpyToSymbol(i_bound, &(userSettings.height), sizeof(int), 0));

        CU_CHK(cudaMalloc((void**)(&H_imdata), wid * hei * sizeof(int)));
        CU_CHK(cudaMemcpyToSymbol(imdata, &(H_imdata), sizeof(int*), 0));

        CU_CHK(cudaMalloc((void**)(&H_x_inc), wid * hei * sizeof(g_real)));
        CU_CHK(cudaMemcpyToSymbol(x_inc, &(H_x_inc), sizeof(g_real*), 0));

        CU_CHK(cudaMalloc((void**)(&H_y_inc), wid * hei * sizeof(g_real)));
        CU_CHK(cudaMemcpyToSymbol(y_inc, &(H_y_inc), sizeof(g_real*), 0));

        CU_CHK(cudaMalloc((void**)(&H_z_inc), wid * hei * sizeof(g_real)));
        CU_CHK(cudaMemcpyToSymbol(z_inc, &(H_z_inc), sizeof(g_real*), 0));

        CU_CHK(cudaMalloc((void**)(&H_ob_id), wid * hei * sizeof(uint16)));
        CU_CHK(cudaMemcpyToSymbol(ob_id, &(H_ob_id), sizeof(uint16*), 0));

        int num_blocks_w = (userSettings.width  + (BLOCK_SIZE-1))/BLOCK_SIZE;
        int num_blocks_h = (userSettings.height + (BLOCK_SIZE-1))/BLOCK_SIZE;
        grid_conf =  dim3(num_blocks_w, num_blocks_h);
        block_conf = dim3(BLOCK_SIZE, BLOCK_SIZE);
    }

    void free_frame_bufs(void)
    {
        CU_CHK(cudaFree(H_imdata));
        CU_CHK(cudaFree(H_x_inc));
        CU_CHK(cudaFree(H_y_inc));
        CU_CHK(cudaFree(H_z_inc));
        CU_CHK(cudaFree(H_ob_id));
    }

    void set_render_state(SharcSettings* settings)
    {
        float s_elev = sin(settings->cam_elev);
        float c_elev = cos(settings->cam_elev);
        float s_rot  = sin(settings->cam_rot);
        float c_rot  = cos(settings->cam_rot);
        float H_cam_n1 = c_elev*c_rot;
        float H_cam_n2 = c_elev*s_rot;
        float H_cam_n3 = s_elev;
        float scr_asp = (float)((double)userSettings.height / (double)userSettings.width);

        CU_CHK(cudaMemcpyToSymbol(screen_aspect, &(scr_asp),  sizeof(float), 0));

        CU_CHK(cudaMemcpyToSymbol(cam_x, &(settings->cam_x),  sizeof(float), 0));
        CU_CHK(cudaMemcpyToSymbol(cam_y, &(settings->cam_y),  sizeof(float), 0));
        CU_CHK(cudaMemcpyToSymbol(cam_z, &(settings->cam_z),  sizeof(float), 0));

        CU_CHK(cudaMemcpyToSymbol(cam_n1, &(H_cam_n1),  sizeof(float), 0));
        CU_CHK(cudaMemcpyToSymbol(cam_n2, &(H_cam_n2),  sizeof(float), 0));
        CU_CHK(cudaMemcpyToSymbol(cam_n3, &(H_cam_n3),  sizeof(float), 0));

        CU_CHK(cudaMemcpyToSymbol(elev_sin, &(s_elev),  sizeof(float), 0));
        CU_CHK(cudaMemcpyToSymbol(elev_cos, &(c_elev),  sizeof(float), 0));
        CU_CHK(cudaMemcpyToSymbol(rot_sin,  &(s_rot),   sizeof(float), 0));
        CU_CHK(cudaMemcpyToSymbol(rot_cos,  &(c_rot),   sizeof(float), 0));

        CU_CHK(cudaMemcpyToSymbol(skybackground,    &(settings->sky_color),     sizeof(int),   0));
        CU_CHK(cudaMemcpyToSymbol(floorbackground,  &(settings->floor_color),   sizeof(int),   0));
        CU_CHK(cudaMemcpyToSymbol(zoom,             &(settings->zoom_aspect),   sizeof(float), 0));
    }
}
