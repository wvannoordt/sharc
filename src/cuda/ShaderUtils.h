#ifndef SHAD_UTILS_H
#define SHAD_UTILS_H
#include "Typedef.h"

#define trunc_01(myval) (((myval)<0) ? 0 : ((myval) > 1 ? 1 : (myval)))

//vector operations
#define s_vecnorm(myvec) (sqrt(myvec[0]*myvec[0]+myvec[1]*myvec[1]+myvec[2]*myvec[2]))

namespace sharc
{
    __device__ void get_cam_normals(const int& i, const int& j, vec3& n);
}

#endif
