#ifndef MDECODERCLASS_H
#define MDECODERCLASS_H

#ifndef INT64_C
#define INT64_C
#define UINT64_C
#endif

#ifdef __cplusplus
extern "C" {
#endif
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#ifdef __cplusplus
}
#endif

#include <Windows.h>
#include <WinDef.h>
#include <Winbase.h>

#include "GlobalHeader.h"

void rgbToBGR_Mirror(unsigned char* bgrData, int dataSize, long width, long height, bool rgbToBgr, bool mirror);
void SaveFrame(unsigned char *pRGBBuf, int linesize, int width, int height, const char *fileName);

typedef void (*MDisplay)(unsigned char *pBuf, int bufSize ,int Width, int Height, void * pContext);
typedef void (*MoveToThreadCB)(void * pContext);
typedef void (*RemoveFromThreadCB)(void * pContext);


class MDecoderClass
{
public:
    MDecoderClass();
    ~MDecoderClass();

public:
    long freeBuffer();
    long threadTerminate();
    long setDisplayFun(MDisplay display, MoveToThreadCB moveToThread, RemoveFromThreadCB removeFromThread, void *pContext);
    long openDecoder(const char *filename);
    long play();
    long pause();
    long stop();

public:
    AVFormatContext *m_pFormatCtx;
    uint32_t             videoStream;
    AVCodecContext  *m_pCodecCtx;
    AVCodec         *m_pCodec;
    AVFrame         *m_pFrame;
    AVFrame         *m_pFrameRGB;
    AVPacket        packet;
    int m_numBytes;
    uint8_t         *m_buffer;
    struct SwsContext *img_convert_ctx;
    HANDLE  m_decodeThreadHandle;
    bool m_pause;
    bool m_stop;

    MDisplay m_displayFun;
    MoveToThreadCB m_moveToThread;
    RemoveFromThreadCB m_removeFromThread;
    void *m_pContext;
};

#endif // MDECODERCLASS_H
