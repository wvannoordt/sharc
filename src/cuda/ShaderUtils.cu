#include "ShaderUtils.h"
#include "CudaData.h"
namespace sharc
{
    __device__ void get_cam_normals(const int& i, const int& j, vec3& n)
    {
        float screen_xyz;
        float i_portion = 0.5 - ((float)i)/(i_bound-1);
        float j_portion = ((float)j)/(j_bound-1) - 0.5;

        //"X" (rot_sin, -rot_cos, 0)
        //"Y" (-rot_cos*elev_sin, -rot_sin*elev_sin, elev_sin)
        screen_xyz = cam_x + zoom*cam_n1 + j_portion*rot_sin*zoom + i_portion*(-rot_cos*elev_sin);
        n[0] = screen_xyz-cam_x;

        screen_xyz = cam_y + zoom*cam_n2 + j_portion*(-rot_cos)*zoom + i_portion*(-rot_sin*elev_sin);
        n[1] = screen_xyz-cam_y;

        screen_xyz = cam_z + zoom*cam_n3 + i_portion*elev_cos;
        n[2] = screen_xyz-cam_z;

        screen_xyz = s_vecnorm(n);
        n[0] /= screen_xyz;
        n[1] /= screen_xyz;
        n[2] /= screen_xyz;
    }
}
