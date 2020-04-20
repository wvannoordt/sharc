#ifndef SHARC_H
#define SHARC_H

#include "ErrorCodes.h"
#include "GpuTest.h"

//This is only for CRITICAL runtime errors that CANNOT be handled elegantly.
#define SHARC_KILL_ASSERT(my_message) {std::cout << "SHARC_KILL_ASSERT called from file " << __FILE__ << ", line " <<  __LINE__ << std::endl; std::cout << my_message << std::endl; abort();}

namespace sharc
{
    extern "C"
    {
        void SHARC_initialize(int argc, char** argv);
        void SHARC_render(void);
        void SHARC_gputest(void);
        void SHARC_finalize(void);
    }

    void reg_error(const char* message, const char* file, const int line, const int error_code);
}

#endif
