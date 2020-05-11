#ifndef CU_ERR_LOG_H
#define CU_ERR_LOG_H

#include "ErrorCodes.h"

#define CU_CHK(my_kernel_call) H_INTERNAL_register_cuda_error(my_kernel_call, __FILE__, __LINE__)

static void H_INTERNAL_register_cuda_error(cudaError er, const char* file, const int line)
{
    int code = (er == cudaSuccess) ? SHARC_ERR_SUCCESS : SHARC_ERR_CUDA;
    if (code!=SHARC_ERR_SUCCESS)
    {
        erkill(code, cudaGetErrorString(er));
    }
}

#endif
