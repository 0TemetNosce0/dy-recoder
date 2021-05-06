#pragma once
#include "AudioResampler.h"

#include <AudioCapture/WASAPIAudioDevices.h>
#include <audioclient.h>
#include <mmdeviceapi.h>
#include <thread>
#include <windows.h>
#include <wrl/client.h>
#include <functional>
    using namespace Microsoft::WRL;
class AudioCapture {
public:
    enum AudioCaptureEnum
    {
        INPUTAUDIO = 0,
        OUTPUTAUDIO,
        };
    AudioCapture(AudioCaptureEnum type);

    ~AudioCapture();

    void changeDevice(QString deviceId);
    bool start();
    void stop();


    std::function<void(uint8_t* data,int samples)> onAudioData = nullptr;
private:
    bool Initialize();
    void captureThread();
    ComPtr<IMMDevice> device;
    ComPtr<IAudioClient> client;
    ComPtr<IAudioCaptureClient> capture;
    ComPtr<IMMDeviceEnumerator> enumerator;
    HANDLE stopSignal;
    HANDLE receiveSignal;
    std::thread captureThr;
    bool processCaptureData();

    QString deviceIdString;
    bool WaitForCaptureSignal(DWORD numSignals, const HANDLE *sigs, DWORD duration);
    //重采樣：44100，float，2通道，packet.
    std::unique_ptr<AudioResampler> resamper = nullptr;
    LPCWSTR stringToLPCWSTR(std::string orig);

    AudioCaptureEnum audioCaptureType = INPUTAUDIO;
    bool isCapture  =false;
};
