QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


SOURCES += \
    AudioCapture.cpp \
    AudioCapture/AudioInputCapture.cpp \
    AudioCapture/AudioOutputCapture.cpp \
    AudioCapture/WASAPIAudioDevices.cpp \
    AudioMeterWidget.cpp \
    AudioRender.cpp \
    DXGICapture.cpp \
    GDICapture.cpp \
    RecoderCore.cpp \
    RenderWidget.cpp \
    VideoRender.cpp \
    capture/AudioCapture/AudioInputCapture.cpp \
    capture/AudioCapture/AudioOutputCapture.cpp \
    capture/AudioCapture/WASAPIAudioDevices.cpp \
    capture/ScreenCapture/DXGIScreenCapture.cpp \
    capture/ScreenCapture/GDIScreenCapture.cpp \
    capture/ScreenCapture/ScreenCapture.cpp \
    capture/ScreenCapture/WindowHelper.cpp \
    main.cpp \
    Widget.cpp \
    mux/Muxer.cpp

HEADERS += \
    AudioCapture.h \
    AudioCapture/AudioInputCapture.h \
    AudioCapture/AudioOutputCapture.h \
    AudioCapture/WASAPIAudioDevices.h \
    AudioMeterWidget.h \
    AudioRender.h \
    DXGICapture.h \
    GDICapture.h \
    RecoderCore.h \
    RenderWidget.h \
    VideoRender.h \
    Widget.h \
    capture/AudioCapture/AudioInputCapture.h \
    capture/AudioCapture/AudioOutputCapture.h \
    capture/AudioCapture/WASAPIAudioDevices.h \
    capture/ScreenCapture/DXGIScreenCapture.h \
    capture/ScreenCapture/GDIScreenCapture.h \
    capture/ScreenCapture/ScreenCapture.h \
    capture/ScreenCapture/WindowHelper.h \
    mux/Muxer.h \
    util/SafeQueue.h



FORMS += \
    Widget.ui


LIBS  += $$PWD/3rd/ffmpeg-4.0.2-win32/lib/avcodec.lib  \
            $$PWD/3rd/ffmpeg-4.0.2-win32/lib/avdevice.lib  \
            $$PWD/3rd/ffmpeg-4.0.2-win32/lib/avfilter.lib  \
            $$PWD/3rd/ffmpeg-4.0.2-win32/lib/avformat.lib  \
            $$PWD/3rd/ffmpeg-4.0.2-win32/lib/avutil.lib  \
            $$PWD/3rd/ffmpeg-4.0.2-win32/lib/postproc.lib  \
            $$PWD/3rd/ffmpeg-4.0.2-win32/lib/swresample.lib  \
            $$PWD/3rd/ffmpeg-4.0.2-win32/lib/swscale.lib

#LIBS  +=  \
#        $$PWD/3rd/ffmpeg-4.0.2-win32/bin/swresample-3.dll \
#        $$PWD/3rd/ffmpeg-4.0.2-win32/bin/swscale-5.dll \
#        $$PWD/3rd/ffmpeg-4.0.2-win32/bin/avcodec-58.dll \
#        $$PWD/3rd/ffmpeg-4.0.2-win32/bin/avdevice-58.dll \
#        $$PWD/3rd/ffmpeg-4.0.2-win32/bin/avfilter-7.dll \
#        $$PWD/3rd/ffmpeg-4.0.2-win32/bin/avformat-58.dll \
#        $$PWD/3rd/ffmpeg-4.0.2-win32/bin/avutil-56.dll \
#        $$PWD/3rd/ffmpeg-4.0.2-win32/bin/postproc-55.dll \


INCLUDEPATH += $$PWD/3rd/ffmpeg-4.0.2-win32/include

LIBS += -lshell32 -luser32 -lD3d9
