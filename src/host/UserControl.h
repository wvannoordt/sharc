#ifndef USER_CONTROL_H
#define USER_CONTROL_H

namespace sharc
{
    void OnKeyPress(unsigned char key, int x, int y);
    void OnMouseMove(int x, int y);
    void OnMouseDrag(int x, int y);
    void OnSpecialKeyPress(int key, int x, int y);
    void OnDisplay(void);
    void DrawTexture(void);
}

#endif
