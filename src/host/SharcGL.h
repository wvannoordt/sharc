#ifndef SHARC_GL_H
#define SHARC_GL_H

namespace sharc
{
    void SharcGLInit(int argc, char** argv, const char* title);
    void SharcInitPixBuffer(void);
    void SharcGLOnClose(void);
    void SharcGLWindow(void);
}

#endif
