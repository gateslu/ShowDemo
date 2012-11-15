/*
 * Copyright (c) 2010, Tae-young Jung
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the <organization>.
 * 4. Neither the name of the <organization> nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY <COPYRIGHT HOLDER> ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// OpenGLView.cpp : implementation file
//

#include "OpenGLView.h"

// COpenGLView

DWORD drawThread(PVOID pContext)
{
    COpenGLView *pThis = (COpenGLView *)pContext;
    wglMakeCurrent(pThis->m_hDC, pThis->m_hRC);
    int n = 0;
    while (n < 100)
    {
        pThis->OnDraw();
        ::Sleep(60);
        n++;
    }
    wglMakeCurrent(NULL, NULL);
    return 0;
}

COpenGLView::COpenGLView() :
    m_hRC(NULL),
    m_hDC(NULL)
{
    loaded = FALSE;

    ratio_x = 1.0;
    ratio_y = 1.0;

    t_width = 0;
    t_height = 0;
}

COpenGLView::~COpenGLView()
{
    OnDestroy();
}

// COpenGLView drawing

void COpenGLView::OnDraw()
{
//    HDC dc = ::GetDC(m_hWnd);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);		// clear screen and depth buffer
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-0.5f);
    if( loaded ){
        glBindTexture( GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
        glTexCoord2f( 0.f, 0.f );
        glVertex3i( 0, 0, 0);

        glTexCoord2f( 0.f, 1.f );
        glVertex3i( 0, t_height, 0);

        glTexCoord2f( 1.f, 1.f );
        glVertex3i( t_width, t_height, 0);

        glTexCoord2f( 1.f, 0.f );
        glVertex3i( t_width, 0, 0);
        glEnd();
    }
    SwapBuffers( m_hDC );
//    SwapBuffers( dc );

//    ::ReleaseDC( m_hWnd, dc );

}

void COpenGLView::glInital()
{
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glGenTextures( 1, &texture );
    glBindTexture(GL_TEXTURE_2D, texture );

    //	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_PRIORITY, 1.0);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glClearColor(0,0,0,0);
}

int COpenGLView::OnCreate(void *handle)
{
    m_hWnd = (HWND)handle;
    if (m_hWnd == NULL)
    {
        return 0;
    }
    RECT targetRect;
    ::GetClientRect(m_hWnd, &targetRect);
    width = targetRect.right-targetRect.left;
    height = targetRect.bottom-targetRect.top;

    // TODO:  Add your specialized creation code here
    int nPixelFormat;					// our pixel format index

    //   static PIXELFORMATDESCRIPTOR pfd = {
    //       sizeof(PIXELFORMATDESCRIPTOR),	// size of structure
    //       1,								// default version
    //       PFD_DRAW_TO_WINDOW |			// window drawing support
    //       PFD_SUPPORT_OPENGL |			// OpenGL support
    //       PFD_DOUBLEBUFFER,				// double buffering support
    //       PFD_TYPE_RGBA,					// RGBA color mode
    //       32,								// 32 bit color mode
    //       0, 0, 0, 0, 0, 0,				// ignore color bits, non-palettized mode
    //       0,								// no alpha buffer
    //       0,								// ignore shift bit
    //       0,								// no accumulation buffer
    //       0, 0, 0, 0,						// ignore accumulation bits
    //       0,								// no z-buffer size
    //       0,								// no stencil buffer
    //       0,								// no auxiliary buffer
    //       PFD_MAIN_PLANE,					// main drawing plane
    //       0,								// reserved
    //       0, 0, 0 };						// layer masks ignored

    static    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),    //上述格式描述符的大小
        1,                                //版本号
        PFD_DRAW_TO_WINDOW |              //格式支持窗口
        PFD_SUPPORT_OPENGL |              //格式必须支持OpenGL
        PFD_DOUBLEBUFFER,                 //必须支持双缓冲
        PFD_TYPE_RGBA,                    //申请RGBA 格式
        24,                               //选定色彩深度
        0, 0, 0, 0, 0, 0, 0, 0,           //忽略RGBA
        0,                                //无累加缓存
        0, 0, 0, 0,                       //忽略聚集位
        0,                               //0,32位Z-缓存(深度缓存)
        0,                                //无蒙板缓存
        0,                                //无辅助缓存
        PFD_MAIN_PLANE,                   //主绘图层
        0,                                //Reserved
        0, 0, 0                           //忽略层遮罩
    };

//    HDC hdc = ::GetDC(m_hWnd);
    m_hDC = ::GetDC(m_hWnd);
    nPixelFormat = ChoosePixelFormat(m_hDC, &pfd);
    /*BOOL success = */SetPixelFormat(m_hDC, nPixelFormat, &pfd);
    m_hRC = wglCreateContext(m_hDC);

//    wglMakeCurrent(m_hDC, m_hRC);
    wglMakeCurrent(NULL, NULL);
    glInital();
//    moveToThread();
    return 0;
}

void COpenGLView::OnDestroy()
{
    // TODO: Add your message handler code here
    wglDeleteContext(m_hRC);
    ::ReleaseDC( m_hWnd, m_hDC );
}

void COpenGLView::OnSize(int cx, int cy)
{

    // TODO: Add your message handler code here
    glViewport( 0, 0, cx, cy );

    glMatrixMode(GL_PROJECTION);	// set projection matrix current matrix
    glLoadIdentity();
    glOrtho( 0, cx, cy, 0, 0, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef( 0, 0, -10.0f );
    glScalef( ratio_x*1.1, ratio_y, 1.f );
}

void COpenGLView::SetParam(int _width, int _height)
{
    //    for( t_width = 2  ; t_width  < _width  ; t_width  *= 2 );
    //    for( t_height = 2 ; t_height < _height ; t_height *= 2 );
    if (_width == 0 || _height == 0)
        return;
    t_width = _width;
    t_height = _height;

    this->ratio_x = (float)t_width/(float)width;
    this->ratio_y = (float)t_height/(float)height;

//    loaded = FALSE;
}

void COpenGLView::SetParamEX(int _width, int _height, float _ratio_x, float _ratio_y)
{
    //    for( t_width = 2  ; t_width  < _width  ; t_width  *= 2 );
    //    for( t_height = 2 ; t_height < _height ; t_height *= 2 );
    if (_width == 0 || _height == 0)
        return;
    t_width = _width;
    t_height = _height;

    this->ratio_x = _ratio_x;
    this->ratio_y = _ratio_y;

    loaded = FALSE;
}


void COpenGLView::LoadTexture(unsigned char* rgba, int _width, int _height)
{
    //    t_width = _width;
    //    t_height = _height;
//    moveToThread();
    glBindTexture(GL_TEXTURE_2D, texture );
    if( loaded )
    {
        glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, _width, _height, GL_RGB, GL_UNSIGNED_BYTE, rgba );
    }
    else{
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, rgba );
        loaded = TRUE;
    }
//    ::InvalidateRect(m_hWnd,NULL,TRUE);
    OnDraw();
    HANDLE testTH = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)drawThread,(PVOID)this,0,NULL);
    CloseHandle(testTH);
}

void COpenGLView::moveToThread()
{
    if (!m_hDC)
        return;
    bool ret = wglMakeCurrent(m_hDC, m_hRC);
    glInital();
}

void COpenGLView::removeFromThread()
{
    wglMakeCurrent(NULL, NULL);
}

