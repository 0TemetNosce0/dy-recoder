#include "AudioOutputPortAudio.h"
#include <portaudio.h>
#include <iostream>
//#include <library/util/Log.h>
using namespace std;
AudioOutputPortAudio::AudioOutputPortAudio()
{

    outputParameters = new PaStreamParameters;
    PaError err = paNoError;
    if ((err = Pa_Initialize()) != paNoError) {
        //        LOG_ERROR("Error when init portaudio: %s", Pa_GetErrorText(err));
        return;
    }
    initialized = true;
    //    int numDevices = Pa_GetDeviceCount();
    //    for (int i = 0 ; i < numDevices ; ++i) {
    //        const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(i);
    //        if (deviceInfo) {
    ////            const PaHostApiInfo *hostApiInfo = Pa_GetHostApiInfo(deviceInfo->hostApi);
    ////            QString name = QString::fromUtf8(hostApiInfo->name) + QStringLiteral(": ") + QString::fromLocal8Bit(deviceInfo->name);
    ////            //qDebug("audio device %d: %s", i, name.toUtf8().constData());
    ////            //qDebug("max in/out channels: %d/%d", deviceInfo->maxInputChannels, deviceInfo->maxOutputChannels);
    //        }
    //    }
    //    memset(outputParameters, 0, sizeof(PaStreamParameters));
    //    outputParameters->device = Pa_GetDefaultOutputDevice();
    //    if (outputParameters->device == paNoDevice) {
    ////        qWarning("PortAudio get device error!");
    //        return;
    //    }
    ////    const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(outputParameters->device);
    ////    //qDebug("DEFAULT max in/out channels: %d/%d", deviceInfo->maxInputChannels, deviceInfo->maxOutputChannels);
    ////    //qDebug("audio device: %s", QString::fromLocal8Bit(Pa_GetDeviceInfo(outputParameters->device)->name).toUtf8().constData());
    //    outputParameters->hostApiSpecificStreamInfo = nullptr;
    //    outputParameters->suggestedLatency = Pa_GetDeviceInfo(outputParameters->device)->defaultHighOutputLatency;
}
AudioOutputPortAudio::~AudioOutputPortAudio()
{
    //    delete outputParameters;
    close();
    if (initialized){
        //Pa_Terminate需要和Pa_Initialize在一个线程,否则:failed PaWinUtil_CoUninitialize calling thread[39524] does not match initializing thread[17912]
        PaError err = Pa_Terminate(); //终止//Do NOT call this if init failed. See document
        if(err != paNoError){
            //            qWarning("Pa_Terminate error: %s", Pa_GetErrorText(err));
        }
    }
    if (outputParameters) {
        delete outputParameters;
        outputParameters = nullptr;
    }

}



bool AudioOutputPortAudio::open(int chn, int sampleRate,int deviceIndex)
{
    //    Pa_OpenStream( &stream, nullptr, outputParameters, sampleRate, 0, 0, nullptr, nullptr );
    //    return isOpen();

    int numDevices = Pa_GetDeviceCount();
    memset(outputParameters, 0, sizeof(PaStreamParameters));
    if(deviceIndex < 0){
        outputParameters->device = Pa_GetDefaultOutputDevice();
    }else if(deviceIndex < numDevices){
        outputParameters->device = deviceIndex;
    }else {
        //        LOG_WARNING("PortAudio get device error!");
        return false;
    }

    //#ifndef Q_OS_WIN
    //            outputParameters->suggestedLatency = 2;
    //#else
    //    outputParameters->suggestedLatency = 0.3;
    //#endif

    const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(outputParameters->device);
    if(chn > deviceInfo->maxOutputChannels){
        //        LOG_WARNING("DEFAULT max in/out channels: %d/%d", deviceInfo->maxInputChannels, deviceInfo->maxOutputChannels);
        //        LOG_WARNING("audio device: %s", Pa_GetDeviceInfo(outputParameters->device)->name);
        return false;
    }

    //    if (outputParameters->device == paNoDevice) {
    //        //        qWarning("PortAudio get device error!");
    //        return false;
    //    }

    outputParameters->hostApiSpecificStreamInfo = nullptr;
    //0不行
    outputParameters->suggestedLatency = Pa_GetDeviceInfo(outputParameters->device)->defaultHighOutputLatency;
    //    outputParameters->suggestedLatency = 0.1;//延迟播放。


    if(stream){
        return true;
    }
    outputParameters->sampleFormat  = paFloat32;//
    outputParameters->channelCount = chn;

    PaError err = Pa_OpenStream(&stream, nullptr, outputParameters, sampleRate, 0, paNoFlag, nullptr, nullptr);
    if (err != paNoError) {
        //        qWarning("Open portaudio stream error: %s", Pa_GetErrorText(err));
        return false;
    }
    //    outputLatency = Pa_GetStreamInfo(stream)->outputLatency;
    Pa_StartStream(stream);
    return true;
}

bool AudioOutputPortAudio::close()
{

    //    if ( stream )
    //    {
    //        if ( !stop && Pa_IsStreamActive( stream ) )
    //        {
    //            const int samplesToWrite = Pa_GetStreamInfo( stream )->outputLatency * sampleRate;
    //            short *silence = new short[ samplesToWrite * outputParameters->channelCount ]();
    //            Pa_WriteStream( stream, silence, samplesToWrite );
    //            delete[] silence;
    //        }
    //        Pa_CloseStream( stream );
    //        stream = nullptr;
    //    }
    if (stream) {
        PaError err = paNoError;
        if (!Pa_IsStreamStopped(stream)){
            err = Pa_StopStream(stream); //may be already stopped: paStreamIsStopped
            if (err != paNoError) {
                //                qWarning("Stop portaudio stream error: %s", Pa_GetErrorText(err));
                //return err == paStreamIsStopped;
            }
        }

        err = Pa_CloseStream(stream);
        if (err != paNoError) {
            //            qWarning("Close portaudio stream error: %s", Pa_GetErrorText(err));
            return false;
        }
        stream = nullptr;
        //        if (stop&&initialized){
        //            err = Pa_Terminate(); //Do NOT call this if init failed. See document
        //            if(err != paNoError){
        //                qWarning("Pa_Terminate error: %s", Pa_GetErrorText(err));
        //            }
        //        }
        return true;
    }
    else {
        return false;
    }
}
//Pa_AbortStream Pa_StopStream然后又播放会有之前outputParameters->suggestedLatency时间
bool AudioOutputPortAudio::pause()
{
    if(Pa_IsStreamActive( stream )){
        //                         Pa_StopStream(stream);//音频处理终止。它等待，直到所有未决的音频缓冲区已经播放，然后才返回。
        Pa_AbortStream(stream);//立即终止音频处理，无需等待挂起的缓冲区完成。
        //        Pa_StopStream(stream);
        //         Pa_Terminate();
        //这个函数释放PortAudio分配的所有资源，因为它是通过调用Pa Initialize()初始化的。
        //在Pa Initialise()多次被调用的情况下，每个调用必须与对应的Pa Terminate()调用匹配。在退出使用PortAudio的程序之前，
        //必须调用Pa Terminate()。如果不这样做，可能会导致严重的资源泄漏
        return true;
    }
    return false;
}
//#include <QDebug>
bool AudioOutputPortAudio::clear()
{
    if (stream) {
        //        PaError err = Pa_StopStream(stream); //may be already stopped: paStreamIsStopped
        //        if (err != paNoError) {
        //            qWarning("Stop portaudio stream error: %s", Pa_GetErrorText(err));
        //            //return err == paStreamIsStopped;
        //        }
        //        err = Pa_CloseStream(stream);
        //        if (err != paNoError) {
        //            qWarning("Close portaudio stream error: %s", Pa_GetErrorText(err));
        //            return false;
        //        }
        //        stream = nullptr;
        //        if (initialized)
        if(Pa_IsStreamActive(stream))
            Pa_AbortStream(stream); //Do NOT call this if init failed. See document
        //                Pa_CloseStream(stream);//丢失音频流。如果音频流是活动的，它会丢弃任何挂起的缓冲区，就像调用了Pa_AbortStream()一样。
        //       Pa_Terminate();
        return true;
    }
    return false;
}
//Pa_StartStream第一帧写入会阻塞一段时间,(Pa_AbortStream,Pa_StopStream会Pa_IsStreamStopped stop)
//写入如果portaudio,满了会阻塞.直到可写.
bool AudioOutputPortAudio::write( uint8_t *buffer, const uint32_t size )
{
    if (Pa_IsStreamStopped(stream))
        Pa_StartStream(stream);
    PaError err = Pa_WriteStream(stream,buffer, size);

    if (err == paUnanticipatedHostError) {
        //        qWarning("Write portaudio stream error: %s", Pa_GetErrorText(err));
        return   false;
    }
    return true;
}



double AudioOutputPortAudio::getSuggestedLatency() const
{
    if(outputParameters){
        return outputParameters->suggestedLatency;
    }else {
        return double(0);
    }

}

