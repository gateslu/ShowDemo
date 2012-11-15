#ifndef DRAWCLASS_H
#define DRAWCLASS_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <Windows.h>
#include <stdint.h>
#include <process.h>

#include "GlobalHeader.h"

class DrawClass
{
public:
    DrawClass();
    virtual ~DrawClass();

    int InitGL(GLvoid);
    GLvoid KillGLWindow();

//    int LoadGLTextures();
    int LoadGLTextures(unsigned char *pBuf, int Width, int Height, GLuint *texture);

    void setDisplayWin(void *handle);        //void*, const HWND hWnd

    GLvoid ReSizeGLScene(GLsizei width, GLsizei height);

    int DrawGLScene(GLvoid);

    void loadData (unsigned char *pBuf, int Width, int Height);

    void setfileName(char *_filename);


    HDC			hDC;		// Private GDI Device Context
    HGLRC		hRC;		// Permanent Rendering Context
    HWND		hWnd;		// Holds Our Window Handle
    int width;
    int height;
    uintptr_t ThreadHandle;
    bool ThreadExitFlag;

    unsigned char *m_pBuf;
    int m_Width;
    int m_Height;

};

#endif // DRAWCLASS_H
