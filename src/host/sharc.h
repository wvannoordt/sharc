#ifndef SHARC_H
#define SHARC_H

namespace sharc
{
    extern "C"
    {
        void SHARC_initialize(int argc, char** argv);
        void SHARC_render(void);
        void SHARC_gputest(void);
        void SHARC_finalize(void);
    }
}

#endif
