#-------------------------------------------------
#
# Project created by QtCreator 2012-10-29T23:27:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShowDemo
TEMPLATE = app


SOURCES += main.cpp\
        showdemo.cpp

HEADERS  += showdemo.h

FORMS    += showdemo.ui


#DESTDIR = $$PWD/ShowDemo-build-desktop/bin
DESTDIR = $$PWD/../bin

win32: LIBS += -L$$PWD/../bin/ -lDrawWindow \
                                                     -lMDecoder

win32: LIBS += -luser32 \
                        -lgdi32 \
                        -lAdvapi32

INCLUDEPATH += $$PWD/../DrawWindow
DEPENDPATH += $$PWD/../DrawWindow

INCLUDEPATH += $$PWD/../MDecoder
DEPENDPATH += $$PWD/../MDecoder

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include
