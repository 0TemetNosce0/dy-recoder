#include "FFmpegMux.h"

FFmpegMux::FFmpegMux()
{

}

bool FFmpegMux::Initialize()
{
    auioEncoder = new FFmpegAudioEncoder();
    return true;
}

bool FFmpegMux::exportFile(QString path)
{



    start();

    return true;
}

void FFmpegMux::start()
{

}

void FFmpegMux::stop()
{

    if(muxThread.joinable()){
        muxThread.join();
    }
}

void FFmpegMux::muxThreadRun()
{

   //取音视频编码数据数据,




    //保存

}
