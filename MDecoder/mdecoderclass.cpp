#include "mdecoderclass.h"

#include "stdlib.h"
#include "stdio.h"
#include <cstdio>
#include <QDebug>

#define DISPLAYBUFZISE (1920*1080*4)

void rgbToBGR_Mirror(unsigned char* bgrData, int dataSize, long width, long height, bool rgbToBgr,bool mirror)
{
    long BUFFSIZE = 1920*4;    //1920*4
    unsigned char *linetmp = (unsigned char *)malloc(BUFFSIZE);
    memset(linetmp, 0, BUFFSIZE);
    unsigned char tmp = 0;
    //bgr-rgb
    if (rgbToBgr)
    {
        for (int i = 0; i < dataSize;)
        {
            tmp = bgrData[i];
            bgrData[i] = bgrData[i+2];
            bgrData[i+2] = tmp;
            i += 3;
        }
    }
    //mirror
    if (mirror)
    {
        memset(linetmp, 0x0, BUFFSIZE);
        for (int i=0;i<height/2;i++)
        {
            memset(linetmp, 0, BUFFSIZE);
            memcpy(linetmp, bgrData+i*width*3,width*3);
            memcpy(bgrData+i*width*3, bgrData+(height-i-1)*width*3,width*3);
            memcpy(bgrData+(height-i-1)*width*3, linetmp,width*3);
        }
    }
    free(linetmp);
}

//保存rgb数据，加头信息和文件信息
void SaveFrame(unsigned char *pRGBBuf, int linesize, int width, int height, const char * fileName)
{
    FILE *pFile;
    int  y;
    pFile=fopen(fileName, "wb");
    if(pFile==NULL)
    {
        printf("pFile is null");
        return;
    }

    enum AVPixelFormat bmp_fmt = AV_PIX_FMT_BGR24;
    int bytes = avpicture_get_size(bmp_fmt, width, height);
    int len = bytes + sizeof(BMP_FILE_HDR) + sizeof(BMP_INFO_HDR);
    //    qint64 size = 3*width*height;

    uint8_t *rgb_data = (uint8_t *)malloc(bytes);
    uint8_t *dst_data = (uint8_t *)malloc(len);
    memset(dst_data, 0x0, len);

    BMP_FILE_HDR *fh = (BMP_FILE_HDR *)dst_data;
    BMP_INFO_HDR *bh = (BMP_INFO_HDR *)(dst_data + sizeof(BMP_FILE_HDR));
    fh->bfType = 0x4D42;
    fh->bfSize = sizeof(BMP_FILE_HDR) + sizeof(BMP_INFO_HDR) + bytes;
    fh->bfOffBits = sizeof(BMP_FILE_HDR) + sizeof(BMP_INFO_HDR);
    bh->biSize = sizeof(BMP_INFO_HDR);
    bh->biWidth = width;
    bh->biHeight = height;
    bh->biPlanes = 1;
    bh->biBitCount = 24;
    bh->biCompression = 0;
    bh->biSizeImage = 0;
    bh->biXPelsPerMeter = 0;
    bh->biYPelsPerMeter = 0;
    bh->biClrUsed = 0;
    bh->biClrImportant = 0;

    fwrite(fh, 1, fh->bfOffBits, pFile);

    for(y=0; y<height; y++)
        memcpy(rgb_data+y*width*3, (const char*)pRGBBuf+y*linesize, width*3);

    rgbToBGR_Mirror(rgb_data, bytes, width, height, true, true);

    for(y=0; y<height; y++)
        fwrite((const char*)rgb_data+y*width*3, 1, width*3, pFile);

    fclose(pFile);
}

//解码
DWORD DecodeThread(PVOID pContext)
{
    MDecoderClass *pThis = (MDecoderClass*)pContext;
    pThis->m_moveToThread(pThis->m_pContext);
    unsigned char *frameBuf = (unsigned char *)malloc(DISPLAYBUFZISE);
    memset(frameBuf, 0, DISPLAYBUFZISE);
    AVPacket packet;
    int frameFinished;
    int i =0;
    int rc = 0;
    int drop = 0;
    //读视频帧
    while(true)
    {
        av_init_packet(&packet);
        //            rc = av_read_packet(pThis->m_pFormatCtx,&packet); /* 获取一个包的数据 */
        //          if (rc != 0) break;
        if (av_read_frame(pThis->m_pFormatCtx, &packet) < 0)
            break;
        memset(frameBuf, 0, DISPLAYBUFZISE);
        while (pThis->m_pause)
            ::Sleep(50);
        if (pThis->m_stop)
            break;
        if(packet.stream_index == pThis->videoStream)
        {

            int result;
            avcodec_decode_video2(pThis->m_pCodecCtx,pThis->m_pFrame,&frameFinished,
                                  &packet);
            // Did we get a video frame?
            if(frameFinished)
            {
                //讲得到的YUV数据转换成RGB数据
                if (pThis->img_convert_ctx)
                    pThis->img_convert_ctx = sws_getCachedContext(pThis->img_convert_ctx,pThis->m_pCodecCtx->width,
                                                                  pThis->m_pCodecCtx->height,
                                                                  pThis->m_pCodecCtx->pix_fmt,
                                                                  pThis->m_pCodecCtx->width,
                                                                  pThis->m_pCodecCtx->height,
                                                                  AV_PIX_FMT_RGB24,
                                                                  SWS_BICUBIC,NULL,
                                                                  NULL,NULL);
                else
                    pThis->img_convert_ctx = sws_getContext(pThis->m_pCodecCtx->width,
                                                            pThis->m_pCodecCtx->height,
                                                            pThis->m_pCodecCtx->pix_fmt,
                                                            pThis->m_pCodecCtx->width,
                                                            pThis->m_pCodecCtx->height,
                                                            AV_PIX_FMT_RGB24,
                                                            SWS_BICUBIC,NULL,
                                                            NULL,NULL);
                result = sws_scale(pThis->img_convert_ctx,
                                   (const uint8_t* const*)pThis->m_pFrame->data,
                                   pThis->m_pFrame->linesize,
                                   0,
                                   pThis->m_pCodecCtx->height,
                                   pThis->m_pFrameRGB->data,
                                   pThis->m_pFrameRGB->linesize);

                /**/
                //还需要考虑linesize
//                if (pThis->m_pFrame->pict_type == AV_PICTURE_TYPE_I)
//                {
                    pThis->m_displayFun(pThis->m_pFrameRGB->data[0], pThis->m_numBytes, pThis->m_pCodecCtx->width, pThis->m_pCodecCtx->height, pThis->m_pContext);
//                }
                qDebug() << i << pThis->m_pCodecCtx->bit_rate <<  av_q2d(pThis->m_video_st->codec->time_base) << "******************************************************************************";
                qDebug() << pThis->m_pFrame->width << pThis->m_pFrame->height;
                //                qDebug() << packet.pts << packet.pos << packet.size << packet.stream_index  ;
                //                qDebug() << "AVPictureType" << pThis->m_pFrame->pict_type;
                //                qDebug() << pThis->m_pFrame->pts << pThis->m_pFrame->pkt_pts << pThis->m_pFrame->pkt_dts <<  pThis->m_pFrame->pkt_pos <<  pThis->m_pFrame->pkt_duration;
                //                qDebug() << "******************************************************************************";
                i++;
            }
        }
        //是否有其他方法可以控制帧率?
        ::Sleep(10);
    }
    // Free the packet that was allocated by av_read_frame
    pThis->m_removeFromThread(pThis->m_pContext);
    av_free_packet(&packet);
    free(frameBuf);
    return 0;
}

MDecoderClass::MDecoderClass() :
    m_decodeThreadHandle(NULL),
    m_pFrame(NULL),
    m_pFrameRGB(NULL),
    m_pFormatCtx(NULL),
    m_buffer(NULL),
    img_convert_ctx(NULL),
    m_pause(false),
    m_stop(false),
    m_displayFun(NULL),
    m_moveToThread(NULL),
    m_removeFromThread(NULL),
    m_pContext(NULL)
{
    avcodec_register_all();
#if CONFIG_AVDEVICE
    avdevice_register_all();
#endif
#if CONFIG_AVFILTER
    avfilter_register_all();
#endif
    av_register_all();
    avformat_network_init();
}

MDecoderClass::~MDecoderClass()
{
    m_displayFun = NULL;
    m_pContext = NULL;
    threadTerminate();
    freeBuffer();
    this->m_moveToThread = NULL;
    this->m_removeFromThread = NULL;
}

long MDecoderClass::freeBuffer()
{
    if (m_pFrame)
        avcodec_free_frame(&m_pFrame);
    if (m_pFrameRGB)
        avcodec_free_frame(&m_pFrameRGB);
    if (m_pFormatCtx)
        avformat_free_context(m_pFormatCtx);
    if (m_buffer)
        av_free(m_buffer);
    m_pFrame = NULL;
    m_pFrameRGB = NULL;
    m_pFormatCtx = NULL;
    m_pCodecCtx = NULL;
    m_pCodec = NULL;
    m_buffer = NULL;

    return 0;
}

long MDecoderClass::threadTerminate()
{
    this->m_stop = true;
    if (this->m_pause)
        this->m_pause = false;
    WaitForSingleObject(m_decodeThreadHandle, INFINITE);
    CloseHandle(m_decodeThreadHandle);
    m_decodeThreadHandle = NULL;
    return 0;
}

long MDecoderClass::setDisplayFun(MDisplay display,     MoveToThreadCB moveToThread,
                                  RemoveFromThreadCB removeFromThread, void *pContext)
{
    if (!display)
        return 1;
    this->m_displayFun = display;
    this->m_moveToThread = moveToThread;
    this->m_removeFromThread = removeFromThread;
    m_pContext = pContext;
    return 0;
}

long MDecoderClass::openDecoder(const char *filename, int &_Width, int &_Height)
{
    threadTerminate();
    freeBuffer();

    m_pFormatCtx = avformat_alloc_context();
    int ret = avformat_open_input(&m_pFormatCtx, filename, NULL, NULL);
    if(ret !=0 )
        return 1; // 不能打开此文件

    if(av_find_stream_info(m_pFormatCtx)<0)
        return 1;
    av_dump_format(m_pFormatCtx, 0, filename, false);

    uint32_t i;
    // 寻找第一个视频流videoStream=-1;
    for(i=0; i<m_pFormatCtx->nb_streams; i++)
        if(m_pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO)
        {
            videoStream=i;
            break;
        }
    if(videoStream==-1)
        return 1;
    m_pCodecCtx = m_pFormatCtx->streams[videoStream]->codec;
    m_video_st = m_pFormatCtx->streams[videoStream];
    m_pCodec = avcodec_find_decoder(m_pCodecCtx->codec_id);
    if(m_pCodec==NULL)
        return 1;

    //必须注释掉，不然会花屏
//    if(m_pCodec->capabilities & CODEC_CAP_TRUNCATED)
//        m_pCodecCtx->flags|=CODEC_FLAG_TRUNCATED;

    if(avcodec_open(m_pCodecCtx, m_pCodec)<0)
        return 1;

    m_pFrame = avcodec_alloc_frame();
    m_pFrameRGB = avcodec_alloc_frame();
    m_numBytes =avpicture_get_size(AV_PIX_FMT_RGB24, m_pCodecCtx->width,  m_pCodecCtx->height);
    m_buffer=(uint8_t *)av_malloc(m_numBytes*sizeof(uint8_t));

    avpicture_fill((AVPicture *)m_pFrameRGB,m_buffer, AV_PIX_FMT_RGB24,m_pCodecCtx->width, m_pCodecCtx->height);
    _Width = m_pCodecCtx->width;
    _Height = m_pCodecCtx->height;
    return 0;
}

long MDecoderClass::play()
{
    if (!m_pFormatCtx)
        return 0;

    if (m_decodeThreadHandle)
    {
        threadTerminate();
    }
    this->m_stop = false;
    this->m_pause = false;
    m_decodeThreadHandle = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)DecodeThread,(PVOID)this,0,NULL);

    return 0;
}

long MDecoderClass::pause()
{
    if (!this->m_pause)
        this->m_pause = true;
    else
        this->m_pause = false;

    return 0;
}

long MDecoderClass::stop()
{
    if (this->m_pause)
        this->m_pause = false;
    this->m_stop = true;

    return 0;
}
