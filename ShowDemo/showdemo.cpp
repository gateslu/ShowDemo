#include "showdemo.h"
#include "ui_showdemo.h"


#include "drawwindow.h"
#include "GlobalHeader.h"

#define BUFFSIZE (1920*1080*4)

#define STARTTIME(BeginMse) { QDateTime BeginDT = QDateTime::currentDateTime(); \
    BeginMse = BeginDT.toMSecsSinceEpoch(); \
    qDebug() << "Begin Time: " << BeginDT.toString("hh:mm:ss.zzz");  } \

#define ENDTIME(EndMse) { QDateTime EndDT = QDateTime::currentDateTime(); \
    EndMse = EndDT.toMSecsSinceEpoch(); \
    qDebug() << "End Time: " << EndDT.toString("hh:mm:ss.zzz");}  \

#define TIMEDIFFERENCE(BeginMse,EndMse) { \
    qDebug() << "Usage Time: " << EndMse-BeginMse << "ms"; }\

int iFrame = 0;

DWORD testThread(PVOID pContext)
{
    qDebug() << "testThread" << QThread::currentThreadId();
    ShowDemo *pThis = (ShowDemo *)pContext;
    MoveToThread(pThis->m_drawhandle);
    int n = 0;
    while (n < 100)
    {
        DrawWindow(pThis->m_drawhandle, pThis->buffer, pThis->Width, pThis->Height);
        ::Sleep(60);
        n++;
    }

    char *szFilename = (char *)malloc(256);
    unsigned char *bmpBuf = (unsigned char*)malloc(pThis->Width*pThis->Height*4);
    memcpy(bmpBuf,pThis->buffer,pThis->Width*pThis->Height*3);
    sprintf(szFilename, "ThreadBmp_%d.bmp", (int)pContext);
    //    RgbToBGR_Mirror(bmpBuf, pThis->Width*pThis->Height*3, pThis->Width, pThis->Height, true, true);
    SaveToBMP(bmpBuf, pThis->Width*3, pThis->Width, pThis->Height, szFilename);
    free(szFilename);
    free(bmpBuf);

    RemoveFromThread(pThis->m_drawhandle);

    pThis->testTH = NULL;
    return 0;
}

static void mMoveToThread(void * pContext)
{
    qDebug() << QThread::currentThreadId();
    ShowDemo *pThis = (ShowDemo *)pContext;
    MoveToThread(pThis->m_drawhandle);
}

static void mRemoveFromThread(void * pContext)
{
    qDebug() << QThread::currentThreadId();
    ShowDemo *pThis = (ShowDemo *)pContext;
    RemoveFromThread(pThis->m_drawhandle);
}

static void mDisplay(unsigned char *pBuf, int bufSize ,int Width, int Height, void * pContext)
{
    ShowDemo *pThis = (ShowDemo *)pContext;
    //    pThis->display(pBuf,Width,Height);
    //    qDebug() << Width << Height;
    //    if( iFrame ==30 )
    //    {
    pThis->Width = Width;
    pThis->Height = Height;
    if (pThis->buffer == NULL || pBuf == NULL)
        return;
    memcpy(pThis->buffer, pBuf,bufSize);
    pThis->display(pThis->buffer,pThis->Width,pThis->Height);
    //    }
    //    if( iFrame <=30 && iFrame >20 /*&& pFrame->key_frame == 1*/)
    //    {
    //        char *szFilename = (char *)malloc(256);
    //        unsigned char *bmpBuf = (unsigned char*)malloc(Width*Height*4);
    //        memcpy(bmpBuf,pBuf,bufSize);
    //        sprintf(szFilename, "displaytest%d.bmp", iFrame);
    //        RgbToBGR_Mirror(bmpBuf, bufSize, Width, Height, true, true);
    //        SaveToBMP(bmpBuf, Width*3, Width, Height, szFilename);
    //        free(szFilename);
    //        free(bmpBuf);
    //    }
    iFrame++;
}

void LoadBMPData(unsigned char *pBuf, int &bufSize, int &Width, int &Height,char *Filename)				// Loads A Bitmap Image
{
    unsigned char *buffer = (unsigned char *)malloc(1920*1080*4);
    FILE *File=NULL;									// File Handle

    if (!Filename)										// Make Sure A Filename Was Given
    {
        return;									// If Not Return NULL
    }

    File=fopen(Filename,"r");							// Check To See If The File Exists
    int i, j, k,k1,k2, pixel_size;
    uint32_t image_size,line_bytes,offset;
    if (File)											// Does The File Exist?
    {
        fseek(File, 0L, SEEK_END);
        int fliesize = ftell(File);         //得到文件大小
        fseek(File, 0L, SEEK_SET);
        size_t size = fread( (void *)buffer, fliesize, 1, File );
        BMP_FILE_HDR *fh = (BMP_FILE_HDR *)buffer;
        BMP_INFO_HDR *bh = (BMP_INFO_HDR *)(buffer + sizeof(BMP_FILE_HDR));

        pixel_size = bh->biBitCount >> 3;
        line_bytes = bh->biWidth * pixel_size + 3 - ((bh->biWidth * pixel_size + 3) & 3);
        image_size = bh->biHeight * line_bytes;

        int buffSize = fh->bfSize;    //得到文件大小
        Width = bh->biWidth;
        Height = bh->biHeight;
        int infoSize = sizeof(BMP_FILE_HDR)+sizeof(BMP_INFO_HDR);

        if(bh->biBitCount <= 8)
            offset = 1 << bh->biBitCount;
        else
            offset = 0;
        unsigned char tmp = 0;
        unsigned char *bgrData = buffer+infoSize+4*offset;
        int dataSize = fliesize-infoSize-4*offset;
        bufSize = dataSize;
        if (bh->biBitCount == 8)
        {
            memcpy(pBuf, bgrData, dataSize);
        }
        else if (bh->biBitCount == 24)
        {
            //bgr-rgb
            for (int i = 0; i < dataSize;)
            {
                tmp = bgrData[i];
                bgrData[i] = bgrData[i+2];
                bgrData[i+2] = tmp;
                i += 3;
            }
            //mirror
            unsigned char *linetmp = (unsigned char *)malloc(BUFFSIZE);
            for (int i=0;i<bh->biHeight/2;i++)
            {
                memset(linetmp, 0, BUFFSIZE);
                memcpy(linetmp, bgrData+i*bh->biWidth*3,bh->biWidth*3);
                memcpy(bgrData+i*bh->biWidth*3, bgrData+(bh->biHeight-i)*bh->biWidth*3,bh->biWidth*3);
                memcpy(bgrData+(bh->biHeight-i)*bh->biWidth*3, linetmp,bh->biWidth*3);
            }
            free(linetmp);
            memcpy(pBuf, bgrData, dataSize);
        }
        fclose(File);							   // Close The Handle
        free(buffer);
        return;                                     // Load The Bitmap And Return A Pointer
    }
    free(buffer);
    return;										  // If Load Failed Return NULL
}

ShowDemo::ShowDemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowDemo),
    m_drawhandle(NULL),
    m_decoder(NULL),
    testTH(NULL)
{
    ui->setupUi(this);
    Width=0;
    Height=0;
    buffer = (unsigned char *)malloc(BUFFSIZE);
    memset(buffer, 0, BUFFSIZE);

    //    int t_width, t_height;

    //    for( t_width = 2  ; t_width  < Width  ; t_width  *= 2 );
    //    for( t_height = 2 ; t_height < Height ; t_height *= 2 );

    //    if( buffer != NULL ) delete[] rgba;
    //    buffer = new unsigned char[t_width*t_height*3];
    enableUI(false);

    setDecoder();
    on_InitDraw_clicked();

    ui->filePath->setText(QString("%1/%2/%3").arg(qApp->applicationDirPath()).arg("demovideo").arg("123.avi"));
}

ShowDemo::~ShowDemo()
{
    free(buffer);
    buffer = NULL;
    delete ui;
}

void ShowDemo::enableUI(bool _isEnable)
{
    ui->InitDraw->setEnabled(!_isEnable);
    ui->ReleaseDraw->setEnabled(_isEnable);
    ui->ResizeWin->setEnabled(_isEnable);
    ui->DrawWindow->setEnabled(_isEnable);
}

void ShowDemo::setDecoder()
{
    m_decoder = InitDecoder();
    if (m_decoder)
        setDisplay();
}

void ShowDemo::display(unsigned char *pBuf, int Width, int Height)
{
    DrawWindow(m_drawhandle, pBuf, Width, Height);
}

void ShowDemo::setDisplay()
{
    SetDisplay(m_decoder, mDisplay, mMoveToThread, mRemoveFromThread, this);
}

void ShowDemo::on_InitDraw_clicked()
{
    if (m_drawhandle)
        return;
    m_drawhandle = InitGLDraw();

    if (m_drawhandle == NULL)
        return;
    int w = ui->Showlabel->width();
    int h = ui->Showlabel->height();
    long ret = AddNewDraw(m_drawhandle, ui->Showlabel->winId(),w,h,1.000,1.000);

    enableUI(true);
    //    on_LoadImage_clicked();
}

void ShowDemo::on_LoadImage_clicked()
{
    Width=0;
    Height=0;
    int bufSize = 0;
    char *szFilename = (char *)malloc(256);
    unsigned char *bmpBuf = (unsigned char*)malloc(1920*1080*4);

    memset(bmpBuf, 0, BUFFSIZE);
    LoadBMPData(bmpBuf, bufSize, Width, Height,ui->ImagePath->text().toLocal8Bit().data());

    memcpy(buffer, bmpBuf,bufSize);
    sprintf(szFilename, "LoadedBuftest.bmp");
    //    RgbToBGR_Mirror(bmpBuf, bufSize, Width, Height, true, true);
    SaveToBMP(bmpBuf, Width*3, Width, Height, szFilename);

    QImage image(bmpBuf, Width, Height,QImage::Format_RGB888);
    ui->previewLB->setPixmap(QPixmap::fromImage(image));

    free(szFilename);
    free(bmpBuf);
}

void ShowDemo::on_ReleaseDraw_clicked()
{
    if(ReleaseGLDraw(m_drawhandle))
        enableUI(false);
}

void ShowDemo::on_DrawWindow_clicked()
{
    qint64 BeginMse = 0,EndMse = 0;
    STARTTIME(BeginMse);
    //    MoveToThread(m_drawhandle);
    display( buffer, Width, Height);
    //    DrawWindow(m_drawhandle, buffer, Width, Height);

    ENDTIME(EndMse);
    TIMEDIFFERENCE(BeginMse,EndMse);
}

void ShowDemo::on_ResizeWin_clicked()
{
    float vWidth = (float)ui->Showlabel->width();
    float vHeight = (float)ui->Showlabel->height();
    if (Width==0 || Height==0)
        return;

    qint64 BeginMse = 0,EndMse = 0;
    STARTTIME(BeginMse);

    ResizeDisplayWindow(m_drawhandle, (int)vWidth, (int)vHeight);
    ENDTIME(EndMse);
    TIMEDIFFERENCE(BeginMse,EndMse);
}

void ShowDemo::on_openViedoFile_clicked()
{
    OpenDecoder(m_decoder, ui->filePath->text().toLocal8Bit().constData(), Width, Height);
    PreDrawWindow(m_drawhandle,buffer,Width, Height);
}

void ShowDemo::on_playbtn_clicked()
{
    iFrame = 0;
    v_setPlay(m_decoder);
}

void ShowDemo::on_pausebtn_clicked()
{
    v_setPause(m_decoder);
}

void ShowDemo::on_stopbtn_clicked()
{
    v_setStop(m_decoder);
}

void ShowDemo::on_ThreadDraw_clicked()
{
    if (testTH)
        return;
    qDebug() << "on_ThreadDraw_clicked" << QThread::currentThreadId();
    testTH = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)testThread,(PVOID)this,0,NULL);
    CloseHandle(testTH);
}
