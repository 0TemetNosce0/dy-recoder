#include "RecoderCore.h"

#include <AudioCapture/WASAPIAudioDevices.h>

RecoderCore::RecoderCore() {

}

bool RecoderCore::saveSetting() {
    return true;
}

QVector<AudioDeviceInfo> RecoderCore::GetWASAPIAudioDevices() {
    QVector<AudioDeviceInfo> devices;
    WASAPIAudioDevices::GetWASAPIAudioDevices(&devices, false);
    return devices;
}

bool RecoderCore::recoder(std::string path) {
    return false;
}

bool RecoderCore::stop() {
    return false;
}

void RecoderCore::init() {
    //初始化输入设备，输出设备
}

bool RecoderCore::initAudio() {
        audioInputCapture = new AudioInputCapture();
        //

}
