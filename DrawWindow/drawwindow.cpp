//#define DRAWWINDOW_EXPORTS

#include "drawwindow.h"
#include <vector>
#include <map>
#include "OpenGLView.h"
#include "Windows.h"

using namespace std;

//HANDLE ghMutex = NULL;

//typedef map<void* ,COpenGLView*>  MAPDRAWCLASS, *LPMAPDRAWCLASS;
//static MAPDRAWCLASS g_mapDrawClass;

//bool findDrawWinlByWnd(void* _handle)
//{
//    MAPDRAWCLASS::iterator iter = g_mapDrawClass.find(_handle);
//    if (iter != g_mapDrawClass.end())
//    {
//        return true;
//    }
//    return false;
//}

GLHANDLE InitGLDraw ()
{
    COpenGLView *m_DrawC  = new COpenGLView;
    return (GLHANDLE)m_DrawC;
}

long ReleaseGLDraw(GLHANDLE _glhandle )
{
    int iReturn = 1;
    if (_glhandle == NULL)
        return iReturn;

    COpenGLView *m_DrawC = (COpenGLView *)_glhandle;
    delete m_DrawC;
    m_DrawC = NULL;
    iReturn = 0;
    return iReturn;
}

long AddNewDraw(GLHANDLE _glhandle, void *_hwnd,int Width, int Height, float ratio_x, float ratio_y)
{
    int iReturn = 1;
    if (_glhandle == NULL)
        return iReturn;

    COpenGLView *m_DrawC = (COpenGLView *)_glhandle;

    int t_width, t_height;
    t_width = Width;
    t_height = Height;

    m_DrawC->OnCreate(_hwnd);
    m_DrawC->SetParam(t_width,t_height);
    m_DrawC->OnSize(t_width,t_height);

//    for( t_width = 2  ; t_width  < Width  ; t_width  *= 2 );
//    for( t_height = 2 ; t_height < Height ; t_height *= 2 );


    iReturn = 0;

    return iReturn;
}

long ResizeDisplayWindow(GLHANDLE _handle, int Width, int Height)
{
    int iReturn = 1;
    if (_handle == NULL)
        return iReturn;

    COpenGLView *m_DrawC = (COpenGLView *)_handle;
    m_DrawC->SetParam(Width,Height);
    m_DrawC->OnSize(Width,Height);
    iReturn = 0;

    return iReturn;
}

long DrawWindow(GLHANDLE _glhandle, unsigned char *pBuf, int Width, int Height)
{
    int iReturn = 1;
    if (_glhandle == NULL)
        return iReturn;

    COpenGLView *m_DrawC = (COpenGLView *)_glhandle;
    m_DrawC->SetParam(Width,  Height);
    m_DrawC->LoadTexture(pBuf,  Width,  Height);
    iReturn = 0;

    return iReturn;
}

long MoveToThread(GLHANDLE _glhandle)
{
    int iReturn = 1;
    if (_glhandle == NULL)
        return iReturn;

    COpenGLView *m_DrawC = (COpenGLView *)_glhandle;
    m_DrawC->moveToThread();
    return 0;
}

long RemoveFromThread(GLHANDLE _glhandle)
{
    int iReturn = 1;
    if (_glhandle == NULL)
        return iReturn;

    COpenGLView *m_DrawC = (COpenGLView *)_glhandle;
    m_DrawC->removeFromThread();
    return 0;
}
