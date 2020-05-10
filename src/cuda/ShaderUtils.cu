#include "ShaderUtils.h"
#include "CudaData.h"
#include "CuGLInterop.h"
namespace sharc
{
    __device__ void get_cam_normals(const int& i, const int& j, vec3& n)
    {
        float screen_xyz;
        float i_portion = 0.5 - ((float)i)/(layers.Ni-1);
        float j_portion = ((float)j)/(layers.Nj-1) - 0.5;

        //"X" (rot_sin, -rot_cos, 0)
        //"Y" (-rot_cos*elev_sin, -rot_sin*elev_sin, elev_sin)
        screen_xyz = settings.cam_x + settings.zoom_aspect*settings.cam_n[0] + j_portion*settings.rot_sin*settings.zoom_aspect + i_portion*(-settings.rot_cos*settings.elev_sin);
        n[0] = screen_xyz-settings.cam_x;

        screen_xyz = settings.cam_y + settings.zoom_aspect*settings.cam_n[1] + j_portion*(-settings.rot_cos)*settings.zoom_aspect + i_portion*(-settings.rot_sin*settings.elev_sin);
        n[1] = screen_xyz-settings.cam_y;

        screen_xyz = settings.cam_z + settings.zoom_aspect*settings.cam_n[2] + i_portion*settings.elev_cos;
        n[2] = screen_xyz-settings.cam_z;

        screen_xyz = s_vecnorm(n);
        n[0] /= screen_xyz;
        n[1] /= screen_xyz;
        n[2] /= screen_xyz;
    }
}
