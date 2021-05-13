QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


SOURCES += \
    AudioCapture/AudioCapture.cpp \
    AudioCapture/AudioResampler.cpp \
    AudioCapture/WASAPIAudioDevices.cpp \
    AudioMeterWidget.cpp \
    AudioOutputPortAudio.cpp \
    AudioRender.cpp \
    DXGICapture.cpp \
    EncodeAACTest.cpp \
    EncodeAACTest1.cpp \
    GDICapture.cpp \
    RecoderCore.cpp \
    RenderWidget.cpp \
    ScreenCapture/DXGIScreenCapture.cpp \
    ScreenCapture/WindowHelper.cpp \
    VideoRender.cpp \
    encoder/FFmpegAudioEncoder.cpp \
    encoder/FFmpegMux.cpp \
    main.cpp \
    Widget.cpp \
    util/CircleBuffer.cpp \
    util/blog.cpp \
    util/test.cpp

HEADERS += \
    AudioCapture/AudioCapture.h \
    AudioCapture/AudioCapture.h \
    AudioCapture/AudioResampler.h \
    AudioOutputPortAudio.h \
    EncodeAACTest.h \
    EncodeAACTest1.h \
    ScreenCapture/DXGIScreenCapture.h \
    ScreenCapture/WindowHelper.h \
    encoder/FFmpegAudioEncoder.h \
    encoder/FFmpegMux.h \
    util/CircleBuffer.h \
    util/SafeQueue.h \
    AudioCapture/WASAPIAudioDevices.h \
    AudioCapture/WASAPIAudioDevices.h \
    AudioMeterWidget.h \
    AudioRender.h \
    DXGICapture.h \
    GDICapture.h \
    RecoderCore.h \
    RenderWidget.h \
    VideoRender.h \
    Widget.h \
    util/blog.h \
    util/test.h



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

LIBS += -lshell32 -luser32 -lD3d9 -lole32


#DEFINES +=  -D__STDC_CONSTANT_MACROS


HEADERS += \
    AudioCapture/AudioCapture.h \
    AudioCapture/AudioResampler.h \
    util/SafeQueue.h \
    AudioCapture/WASAPIAudioDevices.h \
    AudioCapture/WASAPIAudioDevices.h \
    AudioMeterWidget.h \
    AudioRender.h \
    DXGICapture.h \
    GDICapture.h \
    RecoderCore.h \
    RenderWidget.h \
    VideoRender.h \
    Widget.h \
    util/blog.h



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

LIBS += -lshell32 -luser32 -lD3d9 -lole32 -lD3D11 -lD3DCompiler

LIBS += $$PWD/3rd/portaudio/lib/portaudio_x86.lib



INCLUDEPATH += $$PWD/3rd/portaudio/include

#DEFINES +=  -D__STDC_CONSTANT_MACROS
