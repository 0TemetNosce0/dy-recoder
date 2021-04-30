#pragma once
#include <AudioCapture/WASAPIAudioDevices.h>
#include <audioclient.h>
#include <mmdeviceapi.h>
#include <thread>
#include <windows.h>
#include <wrl/client.h>
using namespace Microsoft::WRL;
class AudioInputCapture {
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
    HANDLE stopSignal;
    HANDLE receiveSignal;
    std::thread captureThr;
    bool processCaptureData();
};
