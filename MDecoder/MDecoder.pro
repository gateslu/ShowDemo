#-------------------------------------------------
#
# Project created by QtCreator 2012-10-30T22:55:14
#
#-------------------------------------------------

QT       -= core gui

TARGET = MDecoder
TEMPLATE = lib
#CONFIG += staticlib

#DEFINES += MDECODER_EXPORTS

DESTDIR = $$PWD/../bin

SOURCES += mdecoder.cpp \
    mdecoderclass.cpp

HEADERS += mdecoder.h \
    mdecoderclass.h

win32: LIBS += -luser32 \
                        -lAdvapi32

#ffmpeg的链接库
win32: LIBS += -L$$PWD/ffmpeg-dev/lib \
          -lavcodec \
          -lavdevice \
          -lavfilter \
          -lavformat \
          -lavutil \
          -lpostproc \
          -lswresample \
          -lswscale

#ffmpeg的头文件
INCLUDEPATH += $$PWD/ffmpeg-dev/include
DEPENDPATH += $$PWD/ffmpeg-dev/include

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include
