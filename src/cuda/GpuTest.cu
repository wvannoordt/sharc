#include "GpuTest.h"
namespace sharc
{
    __global__ void K_gpu_test(int* imdata, const int wid, const int hei)
    {
        int y = 0;
    }

    void gpu_test(void)
    {
        int wid = SHARC_TEST_WID;
        int hei = SHARC_TEST_HEI;
        int* d_image_data;
        cudaMalloc(&d_image_data, wid*hei*sizeof(int));

        cudaFree(d_image_data);
    }
}
