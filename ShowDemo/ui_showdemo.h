/********************************************************************************
** Form generated from reading UI file 'showdemo.ui'
**
** Created: Thu Nov 15 16:23:37 2012
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWDEMO_H
#define UI_SHOWDEMO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowDemo
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *Showlabel;
    QVBoxLayout *verticalLayout;
    QPushButton *InitDraw;
    QPushButton *ResizeWin;
    QPushButton *ReleaseDraw;
    QSpacerItem *verticalSpacer;
    QPushButton *LoadImage;
    QLabel *previewLB;
    QPushButton *DrawWindow;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *openViedoFile;
    QLineEdit *filePath;
    QHBoxLayout *horizontalLayout;
    QPushButton *playbtn;
    QPushButton *pausebtn;
    QPushButton *stopbtn;
    QLineEdit *ImagePath;
    QPushButton *ThreadDraw;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *ShowDemo)
    {
        if (ShowDemo->objectName().isEmpty())
            ShowDemo->setObjectName(QString::fromUtf8("ShowDemo"));
        ShowDemo->resize(954, 717);
        centralWidget = new QWidget(ShowDemo);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        Showlabel = new QLabel(centralWidget);
        Showlabel->setObjectName(QString::fromUtf8("Showlabel"));
        Showlabel->setMinimumSize(QSize(768, 576));
        Showlabel->setMaximumSize(QSize(16777215, 16777215));
        Showlabel->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        Showlabel->setFrameShape(QFrame::Box);

        gridLayout->addWidget(Showlabel, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        InitDraw = new QPushButton(centralWidget);
        InitDraw->setObjectName(QString::fromUtf8("InitDraw"));

        verticalLayout->addWidget(InitDraw);

        ResizeWin = new QPushButton(centralWidget);
        ResizeWin->setObjectName(QString::fromUtf8("ResizeWin"));

        verticalLayout->addWidget(ResizeWin);

        ReleaseDraw = new QPushButton(centralWidget);
        ReleaseDraw->setObjectName(QString::fromUtf8("ReleaseDraw"));

        verticalLayout->addWidget(ReleaseDraw);

        verticalSpacer = new QSpacerItem(20, 119, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        LoadImage = new QPushButton(centralWidget);
        LoadImage->setObjectName(QString::fromUtf8("LoadImage"));

        verticalLayout->addWidget(LoadImage);

        previewLB = new QLabel(centralWidget);
        previewLB->setObjectName(QString::fromUtf8("previewLB"));
        previewLB->setMinimumSize(QSize(160, 144));
        previewLB->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(previewLB);

        DrawWindow = new QPushButton(centralWidget);
        DrawWindow->setObjectName(QString::fromUtf8("DrawWindow"));

        verticalLayout->addWidget(DrawWindow);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        openViedoFile = new QPushButton(centralWidget);
        openViedoFile->setObjectName(QString::fromUtf8("openViedoFile"));

        horizontalLayout_2->addWidget(openViedoFile);

        filePath = new QLineEdit(centralWidget);
        filePath->setObjectName(QString::fromUtf8("filePath"));

        horizontalLayout_2->addWidget(filePath);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        playbtn = new QPushButton(centralWidget);
        playbtn->setObjectName(QString::fromUtf8("playbtn"));

        horizontalLayout->addWidget(playbtn);

        pausebtn = new QPushButton(centralWidget);
        pausebtn->setObjectName(QString::fromUtf8("pausebtn"));

        horizontalLayout->addWidget(pausebtn);

        stopbtn = new QPushButton(centralWidget);
        stopbtn->setObjectName(QString::fromUtf8("stopbtn"));

        horizontalLayout->addWidget(stopbtn);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

        ImagePath = new QLineEdit(centralWidget);
        ImagePath->setObjectName(QString::fromUtf8("ImagePath"));

        gridLayout->addWidget(ImagePath, 3, 0, 1, 1);

        ThreadDraw = new QPushButton(centralWidget);
        ThreadDraw->setObjectName(QString::fromUtf8("ThreadDraw"));

        gridLayout->addWidget(ThreadDraw, 1, 1, 1, 1);

        ShowDemo->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ShowDemo);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 954, 23));
        ShowDemo->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ShowDemo);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ShowDemo->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(ShowDemo);

        QMetaObject::connectSlotsByName(ShowDemo);
    } // setupUi

    void retranslateUi(QMainWindow *ShowDemo)
    {
        ShowDemo->setWindowTitle(QApplication::translate("ShowDemo", "ShowDemo", 0, QApplication::UnicodeUTF8));
        Showlabel->setText(QApplication::translate("ShowDemo", "TextLabel", 0, QApplication::UnicodeUTF8));
        InitDraw->setText(QApplication::translate("ShowDemo", "InitDraw", 0, QApplication::UnicodeUTF8));
        ResizeWin->setText(QApplication::translate("ShowDemo", "ResizeWin", 0, QApplication::UnicodeUTF8));
        ReleaseDraw->setText(QApplication::translate("ShowDemo", "ReleaseDraw", 0, QApplication::UnicodeUTF8));
        LoadImage->setText(QApplication::translate("ShowDemo", "LoadImage", 0, QApplication::UnicodeUTF8));
        previewLB->setText(QApplication::translate("ShowDemo", "TextLabel", 0, QApplication::UnicodeUTF8));
        DrawWindow->setText(QApplication::translate("ShowDemo", "DrawWindow", 0, QApplication::UnicodeUTF8));
        openViedoFile->setText(QApplication::translate("ShowDemo", "OpenVideoFile", 0, QApplication::UnicodeUTF8));
        filePath->setText(QApplication::translate("ShowDemo", "G:\\demovideo\\test.h264", 0, QApplication::UnicodeUTF8));
        playbtn->setText(QApplication::translate("ShowDemo", "play", 0, QApplication::UnicodeUTF8));
        pausebtn->setText(QApplication::translate("ShowDemo", "pause", 0, QApplication::UnicodeUTF8));
        stopbtn->setText(QApplication::translate("ShowDemo", "stop", 0, QApplication::UnicodeUTF8));
        ImagePath->setText(QApplication::translate("ShowDemo", "G:\\ShowDemo\\bin\\ori_vctest22.bmp", 0, QApplication::UnicodeUTF8));
        ThreadDraw->setText(QApplication::translate("ShowDemo", "ThreadDraw", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ShowDemo: public Ui_ShowDemo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWDEMO_H
