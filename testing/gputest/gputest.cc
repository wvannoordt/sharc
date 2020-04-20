#include <iostream>
#include "sharc.h"
using namespace sharc;
int main(int argc, char** argv)
{
    SHARC_initialize(argc, argv);
    SHARC_gputest();
    SHARC_finalize();
    return 0;
}
