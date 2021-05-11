#pragma once
#include <AudioCapture/AudioCapture.h>
#include <AudioCapture/WASAPIAudioDevices.h>
#include <EncodeAACTest.h>
#include <EncodeAACTest1.h>
#include "AudioOutputPortAudio.h"

//内置参数设置
//QJson 配置文件
//日志文件
class RecoderCore {
public:
    RecoderCore();
    void init();

    bool initAudio(); //输出输入初始化

    bool saveSetting();
    //获取输入输出设备info
    QVector<AudioDeviceInfo> GetWASAPIAudioInputDevices();
    QVector<AudioDeviceInfo> GetWASAPIAudioOutputDevices();

    //录制桌面

    //录制摄像头

    //录制摄像头-桌面

    //录制

    //audio bufer
    //audio 合并buffer
    //audio 编码buufer
    //采样率 44100;
    //采样格式 flaot
    //通道数  2;
    //布局 packet;

    bool audioInput = true;
    bool audioOutput = true;

    bool recoder(std::string path);

    bool stop();
    //输入输出meter

    void changeAudioInputDevice(QString deviceId);
      void changeAudioOutputDevice(QString deviceId);
private:
    std::unique_ptr<AudioCapture> audioInputCapture = nullptr;
    std::unique_ptr<AudioCapture> audioOutCapture = nullptr;

//    audioBuffer;
    //test


    EncodeAACTest1 encoderTest;
    AudioOutputPortAudio audioPlay;
};
