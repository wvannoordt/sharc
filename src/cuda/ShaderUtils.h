#ifndef SHAD_UTILS_H
#define SHAD_UTILS_H

#define trunc_01(myval) (((myval)<0) ? 0 : ((myval) > 1 ? 1 : (myval)))

namespace sharc
{
    __device__ void get_cam_normals(const int& i, const int& j, float* n1, float* n2, float* n3);
}

#endif
