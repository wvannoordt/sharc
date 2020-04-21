#include "CudaData.h"
namespace sharc
{
    //image data
    int* H_imdata;
    __device__ int* imdata;

    //launch configuration
    dim3 grid_conf, block_conf;

    __device__ int i_bound, j_bound;
}
