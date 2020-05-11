#include "sharc.h"
#include "CuGLInterop.h"
#include "UserControl.h"
#include "CudaData.h"
namespace sharc
{
    void OnKeyPress(unsigned char key, int x, int y)
    {
        glutPostRedisplay();
    }

    void OnMouseMove(int x, int y)
    {
        /*if (dragMode) return;
        loc.x = x;
        loc.y = y;*/
        glutPostRedisplay();
    }

    void OnMouseDrag(int x, int y)
    {
        /*if (!dragMode) return;
        loc.x = x;
        loc.y = y;*/
        glutPostRedisplay();
    }

    void OnSpecialKeyPress(int key, int x, int y)
    {
        /*if (key == GLUT_KEY_LEFT)  loc.x -= DELTA;
        if (key == GLUT_KEY_RIGHT) loc.x += DELTA;
        if (key == GLUT_KEY_UP)    loc.y -= DELTA;
        if (key == GLUT_KEY_DOWN)  loc.y += DELTA;*/
        glutPostRedisplay();
    }

    void OnDisplay(void)
    {
        int* oglDeviceBuf = 0;
        cudaGraphicsMapResources(1, &cuda_pbo_resource, 0);
        cudaGraphicsResourceGetMappedPointer((void **)&(oglDeviceBuf), NULL, cuda_pbo_resource);
        userSettings.cam_rot += 0.01;
        SHARC_SetRenderState();
        override_OGL_framebuf(oglDeviceBuf);

        //This is where a list of shaders would be built
        SHARC_ComputeShader(SHARC_SHDR_ENVIRON);

        cudaGraphicsUnmapResources(1, &cuda_pbo_resource, 0);
        DrawTexture();
        glutSwapBuffers();
    }
    void DrawTexture(void)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, userSettings.width, userSettings.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(0, userSettings.height);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(userSettings.width, userSettings.height);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(userSettings.width, 0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
}
