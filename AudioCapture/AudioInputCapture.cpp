#include "AudioInputCapture.h"
#include <QDebug>
AudioInputCapture::AudioInputCapture()
{

}

void AudioInputCapture::changeDevice(std::string deviceId)
{
    //改变设备

    //停止綫程
    stop();

    start();

}

void AudioInputCapture::start()
{


    Initialize();




}



void AudioInputCapture::stop()
{
    SetEvent(stopSignal);
    ResetEvent(stopSignal);
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


    ////获取设备
    LPCWSTR deviceId;//TODO设备id
    if(0){//默認設備
        res = enumerator->GetDefaultAudioEndpoint( eCapture , eCommunications ,device.GetAddressOf());
        if (FAILED(res)){
            qDebug("AudioInputCapture GetDefaultAudioEndpoint fail%x"，res);
            return false;
        }

    }else{
        res = enumerator->GetDevice(deviceId, device.GetAddressOf());
        if (FAILED(res)){
            qDebug("AudioInputCapture GetDevice fail%x"，res);
            return false;
        }
    }


    //    HRESULT resSample;
    //    IPropertyStore *store = nullptr;
    //    PWAVEFORMATEX deviceFormatProperties;
    //    PROPVARIANT prop;
    //    resSample = device->OpenPropertyStore(STGM_READ, &store);
    //    if (!FAILED(resSample)) {
    //        resSample =
    //            store->GetValue(PKEY_AudioEngine_DeviceFormat, &prop);
    //        if (!FAILED(resSample)) {
    //            if (prop.vt != VT_EMPTY && prop.blob.pBlobData) {
    //                deviceFormatProperties =
    //                    (PWAVEFORMATEX)prop.blob.pBlobData;
    //                device_sample = std::to_string(
    //                    deviceFormatProperties->nSamplesPerSec);
    //            }
    //        }

    //        store->Release();
    //    }


    //获取格式
    std::unique_ptr<WAVEFORMATEX> wfex;
    DWORD flags = AUDCLNT_STREAMFLAGS_EVENTCALLBACK;
    //初始化IAudioClient
    client.Reset();
    res = device->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr,
                           (void **)client.GetAddressOf());
    if (FAILED(res)){
        //        throw HRError("Failed to activate client context", res);
        return false;

    }

    WAVEFORMATEX * wfexPtr = wfex.get();
    res = client->GetMixFormat(&(wfexPtr));
    if (FAILED(res)){
        //        throw HRError("Failed to get mix format", res);
        return false;
    }

    //    InitFormat(wfex);
    //    DWORD layout = 0;

    //    if (wfex->wFormatTag == WAVE_FORMAT_EXTENSIBLE) {
    //        WAVEFORMATEXTENSIBLE *ext = (WAVEFORMATEXTENSIBLE *)wfex;
    //        layout = ext->dwChannelMask;
    //    }

    //    /* WASAPI is always float */
    //    sampleRate = wfex->nSamplesPerSec;
    //    format = AUDIO_FORMAT_FLOAT;
    //    speakers = ConvertSpeakerLayout(layout, wfex->nChannels);

    //    if (!isInputDevice)
    //        flags |= AUDCLNT_STREAMFLAGS_LOOPBACK;


    res = client->Initialize(AUDCLNT_SHAREMODE_SHARED, flags,
                             BUFFER_TIME_100NS, 0, wfex, nullptr);
    if (FAILED(res)){
        //        throw HRError("Failed to get initialize audio client", res);
        return false;
    }

    //初始化IAudioCaptureClient
    res = client->GetService(__uuidof(IAudioCaptureClient),
                             (void **)capture.Assign());
    if (FAILED(res)){
        //        throw HRError("Failed to create capture context", res);
        return false;
    }
    res = client->SetEventHandle(receiveSignal);
    if (FAILED(res)){
        //        throw HRError("Failed to set event handle", res);

//        captureThread = CreateThread(nullptr, 0, WASAPISource::CaptureThread,
//                                     this, 0, nullptr);
//        if (!captureThread.Valid())
//            throw "Failed to create capture thread";
        auto thr = std::thread();
        captureThr = std::move(thr);
        client->Start();
        active = true;

        blog(LOG_INFO, "WASAPI: Device '%s' [%s Hz] initialized",
             device_name.c_str(), device_sample.c_str());

        return  true;
    }
}

void AudioInputCapture::captureThread()
{
    /* Output devices don't signal, so just make it check every 10 ms */
    DWORD dur = source->isInputDevice ? RECONNECT_INTERVAL : 10;

    HANDLE sigs[2] = {source->receiveSignal, source->stopSignal};

    os_set_thread_name("win-wasapi: capture thread");


    while (WaitForCaptureSignal(2, sigs, dur)) {
        if (!processCaptureData()) {
            reconnect = true;
            break;
        }
    }






    client->stop();
}

bool AudioInputCapture::processCaptureData()
{
    HRESULT res;
    LPBYTE buffer;
    UINT32 frames;
    DWORD flags;
    uint64_t pos, ts;
    UINT captureSize = 0;

    while (true) {
        res = capture->GetNextPacketSize(&captureSize);

        if (FAILED(res)) {
            if (res != AUDCLNT_E_DEVICE_INVALIDATED){
//                blog(LOG_WARNING,
//                     "[WASAPISource::GetCaptureData]"
//                     " capture->GetNextPacketSize"
//                     " failed: %lX",
//                     res);
            }
            return false;
        }

        if (!captureSize)
            break;

        res = capture->GetBuffer(&buffer, &frames, &flags, &pos, &ts);
        if (FAILED(res)) {
            if (res != AUDCLNT_E_DEVICE_INVALIDATED){
//                blog(LOG_WARNING,
//                     "[WASAPISource::GetCaptureData]"
//                     " capture->GetBuffer"
//                     " failed: %lX",
//                     res);
            }
            return false;
        }

//        obs_source_audio data = {};
//        data.data[0] = (const uint8_t *)buffer;
//        data.frames = (uint32_t)frames;
//        data.speakers = speakers;
//        data.samples_per_sec = sampleRate;
//        data.format = format;
//        data.timestamp = useDeviceTiming ? ts * 100 : os_gettime_ns();

//        if (!useDeviceTiming)
//            data.timestamp -= util_mul_div64(frames, 1000000000ULL,
//                                             sampleRate);

//        obs_source_output_audio(source, &data);

        capture->ReleaseBuffer(frames);
    }

    return true;
}



