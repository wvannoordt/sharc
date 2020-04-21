#include <iostream>
#include "sharc.h"
using namespace sharc;
int main(int argc, char** argv)
{
    SHARC_Initialize(argc, argv);
    userSettings.width = 1920;
    userSettings.height = 1080;
    SHARC_AllocateFrameBuffers();
    SHARC_ComputeShader(SHARC_SHDR_TEST);
    SHARC_Offload();
    SHARC_Write("testshader.png");
    SHARC_Finalize();
    return 0;
}
