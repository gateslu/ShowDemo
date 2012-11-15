/********************************************************************************
** Form generated from reading UI file 'showdemo.ui'
**
** Created: Sat Nov 3 02:30:05 2012
**      by: Qt User Interface Compiler version 4.8.2
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
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
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
    QPushButton *DrawWindow;
    QLineEdit *ImagePath;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ShowDemo)
    {
        if (ShowDemo->objectName().isEmpty())
            ShowDemo->setObjectName(QString::fromUtf8("ShowDemo"));
        ShowDemo->resize(869, 677);
        centralWidget = new QWidget(ShowDemo);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        Showlabel = new QLabel(centralWidget);
        Showlabel->setObjectName(QString::fromUtf8("Showlabel"));
        Showlabel->setMinimumSize(QSize(768, 576));
        Showlabel->setMaximumSize(QSize(768, 576));
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

        DrawWindow = new QPushButton(centralWidget);
        DrawWindow->setObjectName(QString::fromUtf8("DrawWindow"));

        verticalLayout->addWidget(DrawWindow);


        gridLayout->addLayout(verticalLayout, 0, 1, 2, 1);

        ImagePath = new QLineEdit(centralWidget);
        ImagePath->setObjectName(QString::fromUtf8("ImagePath"));

        gridLayout->addWidget(ImagePath, 1, 0, 1, 1);

        ShowDemo->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ShowDemo);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 869, 23));
        ShowDemo->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ShowDemo);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ShowDemo->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ShowDemo);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ShowDemo->setStatusBar(statusBar);

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
        DrawWindow->setText(QApplication::translate("ShowDemo", "DrawWindow", 0, QApplication::UnicodeUTF8));
        ImagePath->setText(QApplication::translate("ShowDemo", "G:\\Qt\\qtopengl\\Opengl-build-desktop\\Opengl\\bin\\Data\\AngryBirds1.bmp", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ShowDemo: public Ui_ShowDemo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWDEMO_H
