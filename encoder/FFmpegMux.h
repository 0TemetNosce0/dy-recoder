#pragma once
#include "FFmpegAudioEncoder.h"

#include <QString>
#include <thread>
class FFmpegMux
{
public:
    FFmpegMux();
    bool Initialize();


    bool exportFile(QString path);
    void start();
    void stop();


private:
    void  muxThreadRun();
    std::thread muxThread;
    FFmpegAudioEncoder *auioEncoder = nullptr;
};

