#include "sharc.h"
#include "sharcCuda.h"
#include "GpuTest.h"
#include "ErrorCodes.h"
#include <iostream>
#include <cstdlib>
#include "StlGeom.h"
namespace sharc
{
    void SHARC_initialize(int argc, char** argv)
    {
        StlGeom r;
        r.ReadFromFile("binball.stl");
        r.SavePointCloud("points.csv");
    }
    void SHARC_render(void)
    {

    }
    void SHARC_gputest(void)
    {
        gpu_test();
    }
    void SHARC_finalize(void)
    {
        cuda_finalize();
    }

    void reg_error(const char* message, const char* file, const int line, const int error_code)
    {
        if (error_code != SHARC_ERR_SUCCESS)
        {
            std::cout << file << ", line " << line << ": " << message << std::endl;
            //This is temporary. There should really be a class that handles this. This is TODO.
            abort();
        }
    }
}
