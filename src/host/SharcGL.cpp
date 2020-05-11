#include "CuGLInterop.h"
#include "SharcGL.h"
#include "sharc.h"
#include "UserControl.h"
namespace sharc
{
    void SharcGLInit(int argc, char** argv, const char* title)
    {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
        glutInitWindowSize(userSettings.width, userSettings.height);
        glutCreateWindow(title);
#ifndef __APPLE__
        glewInit();
#endif
        gluOrtho2D(0, userSettings.width, userSettings.height, 0);
        glutKeyboardFunc(OnKeyPress);
        glutSpecialFunc(OnSpecialKeyPress);
        glutPassiveMotionFunc(OnMouseMove);
        glutMotionFunc(OnMouseDrag);
        glutDisplayFunc(OnDisplay);
        SharcInitPixBuffer();
    }

    void SharcInitPixBuffer(void)
    {
        glGenBuffers(1, &pbo);
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo);
        glBufferData(GL_PIXEL_UNPACK_BUFFER, 4*userSettings.width*userSettings.height*sizeof(GLubyte), 0,GL_STREAM_DRAW);
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        cudaGraphicsGLRegisterBuffer(&cuda_pbo_resource, pbo, cudaGraphicsMapFlagsWriteDiscard);
    }

    void SharcGLOnClose(void)
    {
        if (pbo)
        {
            cudaGraphicsUnregisterResource(cuda_pbo_resource);
            glDeleteBuffers(1, &pbo);
            glDeleteTextures(1, &tex);
        }
        SHARC_Finalize();
    }

    void SharcGLWindow(void)
    {
        glutMainLoop();
        atexit(SharcGLOnClose);
    }
}
