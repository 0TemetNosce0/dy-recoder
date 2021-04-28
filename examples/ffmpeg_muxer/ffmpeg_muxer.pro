QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    Widget.cpp

HEADERS += \
    Widget.h

FORMS += \
    Widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS  += $$PWD/../../3rd/ffmpeg-4.0.2-win32/lib/avcodec.lib  \
            $$PWD/../../3rd/ffmpeg-4.0.2-win32/lib/avdevice.lib  \
            $$PWD/../../3rd/ffmpeg-4.0.2-win32/lib/avfilter.lib  \
            $$PWD/../../3rd/ffmpeg-4.0.2-win32/lib/avformat.lib  \
            $$PWD/../../3rd/ffmpeg-4.0.2-win32/lib/avutil.lib  \
            $$PWD/../../3rd/ffmpeg-4.0.2-win32/lib/postproc.lib  \
            $$PWD/../../3rd/ffmpeg-4.0.2-win32/lib/swresample.lib  \
            $$PWD/../../3rd/ffmpeg-4.0.2-win32/lib/swscale.lib

#LIBS  +=  \
#        $$PWD/../../3rd/ffmpeg-4.0.2-win32/bin/swresample-3.dll \
#        $$PWD/../../3rd/ffmpeg-4.0.2-win32/bin/swscale-5.dll \
#        $$PWD/../../3rd/ffmpeg-4.0.2-win32/bin/avcodec-58.dll \
#        $$PWD/../../3rd/ffmpeg-4.0.2-win32/bin/avdevice-58.dll \
#        $$PWD/../../3rd/ffmpeg-4.0.2-win32/bin/avfilter-7.dll \
#        $$PWD/../../3rd/ffmpeg-4.0.2-win32/bin/avformat-58.dll \
#        $$PWD/../../3rd/ffmpeg-4.0.2-win32/bin/avutil-56.dll \
#        $$PWD/../../3rd/ffmpeg-4.0.2-win32/bin/postproc-55.dll


INCLUDEPATH += $$PWD/../../3rd/ffmpeg-4.0.2-win32/include
