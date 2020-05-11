#ifndef ERR_CODE_H
#define ERR_CODE_H

#define SHARC_ERR_SUCCESS 0
#define SHARC_ERR_CUDA 14
#define SHARC_ERR_OGL_SPEC 23

#include <iostream>
#include "sharc.h"
#define erkill(mycode, mymsg) erkill_NM(mycode, mymsg, __LINE__, __FILE__)


static const char* GetSharcErrorString(int er)
{
    switch (er)
    {
        case SHARC_ERR_SUCCESS:  return "SHARC_ERR_SUCCESS:  no error";
        case SHARC_ERR_CUDA:     return "SHARC_ERR_CUDA:     CUDA runtime error";
        case SHARC_ERR_OGL_SPEC: return "SHARC_ERR_OGL_SPEC: Incorrect OpenGL interopability specification";
    }
    return "UNSPECIFIED ERROR";
}


static void erkill_NM(const int code, const char* msg, const int ln, const char* fl)
{
    std::cout << "Sharc kill called from file " << fl << ", line " << ln;
    std::cout << "Message: " << msg << std::endl;
    std::cout << "Error:   " << GetSharcErrorString(code) << std::endl;
    abort();
}

#endif
