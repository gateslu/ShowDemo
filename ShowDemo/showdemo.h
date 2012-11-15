#ifndef SHOWDEMO_H
#define SHOWDEMO_H

#include <QtCore>
#include <QtGui>
#include "qt_windows.h"
#include "drawwindow.h"
#include "mdecoder.h"

namespace Ui {
class ShowDemo;
}

class ShowDemo : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ShowDemo(QWidget *parent = 0);
    ~ShowDemo();
    void enableUI(bool _isEnable);

    void setDecoder();

    void display(unsigned char *pBuf, int Width, int Height);

    void setDisplay();

public slots:
    void on_InitDraw_clicked();

    void on_LoadImage_clicked();

    void on_ReleaseDraw_clicked();

    void on_DrawWindow_clicked();

    void on_ResizeWin_clicked();

    void on_openViedoFile_clicked();

    void on_playbtn_clicked();

    void on_pausebtn_clicked();

    void on_stopbtn_clicked();

    void on_ThreadDraw_clicked();

public:
    int Width;
    int Height;
    unsigned char *buffer;
    GLHANDLE m_drawhandle;

    DECHANDLE m_decoder;

    HANDLE testTH;

private:
    Ui::ShowDemo *ui;

};

#endif // SHOWDEMO_H
