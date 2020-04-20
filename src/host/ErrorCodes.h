#ifndef ERR_CODE_H
#define ERR_CODE_H

#define SHARC_ERR_SUCCESS 0
#define SHARC_ERR_CUDA 14

static const char* GetSharcErrorString(int er)
{
    switch (er)
    {
        case SHARC_ERR_SUCCESS: return "SHARC_ERR_SUCCESS: no error";
        case SHARC_ERR_CUDA:    return "SHARC_ERR_CUDA: CUDA runtime error";
    }
    return "UNSPECIFIED ERROR";
}

#endif
