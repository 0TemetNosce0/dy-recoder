#pragma once
#include <AudioCapture/AudioInputCapture.h>
#include <AudioCapture/WASAPIAudioDevices.h>
#include <string>

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
    QVector<AudioDeviceInfo> GetWASAPIAudioDevices();
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

private:
    AudioInputCapture *audioInputCapture = nullptr;
};
