#pragma once
#include <windows.h>
#include <AudioCapture/WASAPIAudioDevices.h>
#include <mmdeviceapi.h>
#include <audioclient.h>
#include <wrl/client.h>
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
    void InitName();
    void InitClient();
    void InitRender();
    void InitFormat(WAVEFORMATEX *wfex);
    void InitCapture();
private:
    ComPtr<IMMDevice> device;
    ComPtr<IAudioClient> client;
    ComPtr<IAudioCaptureClient> capture;
    ComPtr<IMMDeviceEnumerator> enumerator;
};

