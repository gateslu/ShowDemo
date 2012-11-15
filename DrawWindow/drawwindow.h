#ifndef DRAWWINDOW_H
#define DRAWWINDOW_H

#define DRAWWINDOW_EXPORTS

#ifdef DRAWWINDOW_EXPORTS
#define DRAWWINDOW_API  extern "C" __declspec(dllexport)
#else
#define DRAWWINDOW_API  extern "C" __declspec(dllimport)
#endif

typedef void * GLHANDLE;

DRAWWINDOW_API GLHANDLE InitGLDraw ();
DRAWWINDOW_API long ReleaseGLDraw (GLHANDLE _glhandle);
DRAWWINDOW_API long AddNewDraw (GLHANDLE _glhandle, void *_hwnd, int Width, int Height, float ratio_x, float ratio_y);
DRAWWINDOW_API long ResizeDisplayWindow (GLHANDLE _handle, int Width, int Height);
DRAWWINDOW_API long DrawWindow(GLHANDLE _glhandle, unsigned char *pBuf, int Width, int Height);
DRAWWINDOW_API long MoveToThread(GLHANDLE _glhandle);
DRAWWINDOW_API long RemoveFromThread(GLHANDLE _glhandle);
#endif // DRAWWINDOW_H
