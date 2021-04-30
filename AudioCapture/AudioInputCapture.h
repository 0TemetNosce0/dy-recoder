#pragma once
#include <windows.h>
#include <AudioCapture/WASAPIAudioDevices.h>
#include <mmdeviceapi.h>
#include <audioclient.h>
#include <wrl/client.h>
#include <thread>
using namespace Microsoft::WRL;
class AudioInputCapture
{
public:
    AudioInputCapture();

    ~AudioInputCapture();

    void changeDevice();
    void start();
    void stop();
    bool Initialize();

    void changeDevice(std::string deviceId);
private:

    void captureThread();
    ComPtr<IMMDevice> device;
    ComPtr<IAudioClient> client;
    ComPtr<IAudioCaptureClient> capture;
    ComPtr<IMMDeviceEnumerator> enumerator;
    WinHandle stopSignal;
    WinHandle receiveSignal;
    std::thread captureThr;
    bool processCaptureData();
};

