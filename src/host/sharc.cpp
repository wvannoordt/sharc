#include "sharc.h"
#include "sharcCuda.h"
#include "GpuTest.h"
#include "ErrorCodes.h"
#include "PngWriter.h"
#include <iostream>
#include <cstdlib>
#include "StlGeom.h"
#include "Typedef.h"

namespace sharc
{
    SharcSettings userSettings;
    PngWriter imWriter;
    int* framebuf_host_endpoint;

    void SHARC_Initialize(int argc, char** argv)
    {
        userSettings.Defaults();
    }

    void SHARC_AllocateFrameBuffers(void)
    {
        framebuf_host_endpoint = (int*)malloc(userSettings.width*userSettings.height*sizeof(int));
        cuda_allocate_frame_buffers();
    }

    void SHARC_Render(void)
    {

    }

    void SHARC_Offload(void)
    {
        offload_image_data(framebuf_host_endpoint);
    }

    void SHARC_Write(std::string filename)
    {
        imWriter.write_png(filename.c_str(), userSettings.width, userSettings.height, framebuf_host_endpoint);
    }

    void SHARC_ComputeShader(const int shader_id)
    {
        cuda_compute_shader(shader_id);
    }

    void SHARC_GpuTest(void)
    {
        gpu_test();
    }

    void SHARC_Finalize(void)
    {
        free(framebuf_host_endpoint);
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
