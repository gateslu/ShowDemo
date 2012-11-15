#ifndef MDECODER_H
#define MDECODER_H

#define MDECODER_EXPORTS

#ifdef MDECODER_EXPORTS
#define MDECODER_API  extern "C" __declspec(dllexport)
#else
#define MDECODER_API  extern "C" __declspec(dllimport)
#endif

typedef void * DECHANDLE;

typedef void (*fDataCallback)();
typedef void (*MDisplay)(unsigned char *pBuf, int bufSize ,int Width, int Height, void * pContext);

typedef void (*MoveToThreadCB)(void * pContext);
typedef void (*RemoveFromThreadCB)(void * pContext);

MDECODER_API DECHANDLE InitDecoder (void);
MDECODER_API int ReleaseDecoder (DECHANDLE _dec);
MDECODER_API int OpenDecoder (DECHANDLE _dec, const char *filename, int &_Width, int &_Height);
MDECODER_API int SetCallbackf(DECHANDLE _dec, fDataCallback dcb);
MDECODER_API int SetDisplay(DECHANDLE _dec, MDisplay display, MoveToThreadCB moveToThread, RemoveFromThreadCB removeFromThread, void * pContext);
MDECODER_API int v_setPlay(DECHANDLE _dec);
MDECODER_API int v_setPause(DECHANDLE _dec);
MDECODER_API int v_setStop(DECHANDLE _dec);
MDECODER_API void RgbToBGR_Mirror(unsigned char* bgrData, int dataSize, long width, long height, bool rgbToBgr, bool mirror);
MDECODER_API void SaveToBMP(unsigned char *pRGBBuf, int linesize, int width, int height, const char *fileName);
#endif // MDECODER_H
