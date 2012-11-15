#-------------------------------------------------
#
# Project created by QtCreator 2012-10-29T23:28:33
#
#-------------------------------------------------

QT       -= core gui

TARGET = DrawWindow
TEMPLATE = lib
#CONFIG += staticlib

SOURCES += drawwindow.cpp \
    OpenGLView.cpp \
    drawclass.cpp

HEADERS += drawwindow.h \
    OpenGLView.h \
    drawclass.h

DESTDIR = $$PWD/../bin

win32: LIBS += -L$$PWD/OpenGL/lib/ -lopengl32 \
                                                            -lglu32 \
                                                            -lglut32 \
                                                            -lglui32 \
                                                            -lglew32s \
                                                            -lGLAUX

win32: LIBS += -luser32 \
                        -lgdi32 \
                        -lAdvapi32

INCLUDEPATH += $$PWD/OpenGL/include
DEPENDPATH += $$PWD/OpenGL/include

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include
