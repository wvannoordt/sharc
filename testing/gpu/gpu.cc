#include <iostream>
#include "sharc.h"
using namespace sharc;
int main(int argc, char** argv)
{
    SHARC_Initialize(argc, argv);
    SHARC_GpuTest();
    SHARC_Finalize();
    return 0;
}
