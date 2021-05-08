#include "RecoderCore.h"

#include <AudioCapture/WASAPIAudioDevices.h>
#include <QDebug>
RecoderCore::RecoderCore() {
    initAudio();
    audioPlay.open(2,44100);
}

bool RecoderCore::saveSetting() {
    return true;
}

QVector<AudioDeviceInfo> RecoderCore::GetWASAPIAudioInputDevices() {
    QVector<AudioDeviceInfo> devices;
    WASAPIAudioDevices::GetWASAPIAudioDevices(devices, true);
    return devices;
}

QVector<AudioDeviceInfo> RecoderCore::GetWASAPIAudioOutputDevices()
{
    QVector<AudioDeviceInfo> devices;
    WASAPIAudioDevices::GetWASAPIAudioDevices(devices, false);
    return devices;
}

void RecoderCore::changeAudioInputDevice(QString deviceId)
{
    audioInputCapture->changeDevice(deviceId);

}

void RecoderCore::changeAudioOutputDevice(QString deviceId)
{
    audioOutCapture->changeDevice(deviceId);
}



bool RecoderCore::recoder(std::string path) {
    return false;
}

bool RecoderCore::stop() {
    return false;
}

void RecoderCore::init() {
    //电脑信息获取.
    //初始化输入设备，输出设备
}

bool RecoderCore::initAudio() {
    audioInputCapture.reset(new AudioCapture(AudioCapture::INPUTAUDIO));
    audioInputCapture->onAudioData = [this](uint8_t* data,int samples){
        //        audioPlay.write(  data  ,samples);


        //峰值计算


        //合并buffer。

    };
    //
    encoderTest.init();
    audioOutCapture.reset(new AudioCapture(AudioCapture::OUTPUTAUDIO));
    audioOutCapture->onAudioData = [this](uint8_t* data,int samples){


        //        audioPlay.write(  data  ,samples);


        static int i = 0;
        static bool end = false;
        i++;
        if(end == true){
            return ;
        }
        if(i>400*100*30/400){
            encoderTest.end();
            end =true;
        }else{
   encoderTest.encode(data,samples*2*4);
        }
    };
    return false;
}
