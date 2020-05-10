#include <iostream>
#include "sharc.h"
using namespace sharc;
int main(int argc, char** argv)
{
    SHARC_Initialize(argc, argv);
    SHARC_AllocateFrameBuffers();
    userSettings.cam_elev = 0.1;
    userSettings.cam_rot = 1.7;
    SHARC_SetRenderState();
    SHARC_ComputeShader(SHARC_SHDR_ENVIRON);
    SHARC_Offload();
    SHARC_Write("environshader.png");
    SHARC_Finalize();
    return 0;
}
