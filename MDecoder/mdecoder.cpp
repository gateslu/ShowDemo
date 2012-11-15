#include "mdecoder.h"
#include "mdecoderclass.h"

DECHANDLE InitDecoder(void)
{
    MDecoderClass *m_dec= new MDecoderClass;
    return (DECHANDLE)m_dec;
}

int ReleaseDecoder (DECHANDLE _dec)
{
    if (!_dec)
        return 1;
    MDecoderClass *m_dec = (MDecoderClass *)_dec;
    delete _dec;
    return 0;
}

int OpenDecoder (DECHANDLE _dec, const char *filename, int &_Width, int &_Height)
{
    if (!_dec)
        return 1;

    MDecoderClass *m_dec = (MDecoderClass *)_dec;
    m_dec->openDecoder(filename,_Width, _Height);

    return 1;
}

int SetCallbackf(DECHANDLE _dec, fDataCallback dcb)
{
    if (!_dec)
        return 1;

    MDecoderClass *m_dec = (MDecoderClass *)_dec;

    return 1;
}

int SetDisplay(DECHANDLE _dec, MDisplay display, MoveToThreadCB moveToThread, RemoveFromThreadCB removeFromThread, void *pContext)
{
    if (!_dec)
        return 1;

    MDecoderClass *m_dec = (MDecoderClass *)_dec;
    m_dec->setDisplayFun(display, moveToThread, removeFromThread, pContext);

    return 1;
}

int v_setPlay(DECHANDLE _dec)
{
    if (!_dec)
        return 1;

    MDecoderClass *m_dec = (MDecoderClass *)_dec;
    m_dec->play();

    return 1;
}

int v_setPause(DECHANDLE _dec)
{
    if (!_dec)
        return 1;

    MDecoderClass *m_dec = (MDecoderClass *)_dec;
    m_dec->pause();

    return 1;
}

int v_setStop(DECHANDLE _dec)
{
    if (!_dec)
        return 1;

    MDecoderClass *m_dec = (MDecoderClass *)_dec;
    m_dec->stop();

    return 1;
}

void RgbToBGR_Mirror(unsigned char* bgrData, int dataSize, long width, long height, bool rgbToBgr, bool mirror)
{
    rgbToBGR_Mirror(bgrData, dataSize, width, height, rgbToBgr, mirror);
}

void SaveToBMP(unsigned char *pRGBBuf, int linesize, int width, int height, const char *fileName)
{
    SaveFrame(pRGBBuf, linesize, width, height, fileName);
}
