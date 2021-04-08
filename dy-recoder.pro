QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


SOURCES += \
    AudioCapture.cpp \
    AudioRender.cpp \
    DXGICapture.cpp \
    GDICapture.cpp \
    RenderWidget.cpp \
    VideoRender.cpp \
    main.cpp \
    Widget.cpp

HEADERS += \
    AudioCapture.h \
    AudioRender.h \
    DXGICapture.h \
    GDICapture.h \
    RenderWidget.h \
    VideoRender.h \
    Widget.h



FORMS += \
    Widget.ui
