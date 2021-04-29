#include "AudioInputCapture.h"
#include <QDebug>
AudioInputCapture::AudioInputCapture()
{

}

void AudioInputCapture::changeDevice()
{
//改变设备

   //停止綫程


//停止线程

}

void AudioInputCapture::start()
{



}



void AudioInputCapture::stop()
{

}

bool AudioInputCapture::Initialize()
{
    HRESULT res;
    res = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr,
                           CLSCTX_ALL, __uuidof(IMMDeviceEnumerator),
                           (void **)enumerator.GetAddressOf());
    if (FAILED(res)){
        //        throw ("Failed to create enumerator", res);
        qDebug()<<"ailed to create enumerator"<<QString("%1").arg(res,8,16,QLatin1Char('0')); //不足8位补0;
        abort();
        return false;
    }
    LPCWSTR deviceId;
    res = enumerator->GetDevice(deviceId, device.GetAddressOf());
    if (FAILED(res)){
        qDebug()<<"AudioInputCapture GetDevice fail"<<QString("%1").arg(res,8,16,QLatin1Char('0'));
        return false;
    }

    WAVEFORMATEX* wfex;
    HRESULT res;
    DWORD flags = AUDCLNT_STREAMFLAGS_EVENTCALLBACK;

    res = device->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr,
                           (void **)client.Assign());
    if (FAILED(res))
        throw HRError("Failed to activate client context", res);

    res = client->GetMixFormat(&wfex);
    if (FAILED(res))
        throw HRError("Failed to get mix format", res);

    InitFormat(wfex);

    if (!isInputDevice)
        flags |= AUDCLNT_STREAMFLAGS_LOOPBACK;

    res = client->Initialize(AUDCLNT_SHAREMODE_SHARED, flags,
                             BUFFER_TIME_100NS, 0, wfex, nullptr);
    if (FAILED(res))
        throw HRError("Failed to get initialize audio client", res);
    return  true;
}

void AudioInputCapture::InitName()
{

}

void AudioInputCapture::InitClient()
{

}

void AudioInputCapture::InitRender()
{

}

void AudioInputCapture::InitFormat(WAVEFORMATEX *wfex)
{

}

void AudioInputCapture::InitCapture()
{

}


