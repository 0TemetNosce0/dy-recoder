#include "AudioCapture.h"
#include <QDebug>
#include <util/blog.h>
AudioCapture::AudioCapture(AudioCaptureEnum type)
{

    audioCaptureType = type;
    resamper = std::make_unique<AudioResampler>();

    auto  funValid = [](HANDLE handle)
    {
        return handle && handle != INVALID_HANDLE_VALUE;
    };

    stopSignal = CreateEvent(nullptr, true, false, nullptr);
    if (!funValid(stopSignal)){
        throw "Could not create stop signal";
    }

    receiveSignal = CreateEvent(nullptr, false, false, nullptr);
    if (!funValid(receiveSignal)){
        throw "Could not create receive signal";
    }
}

AudioCapture::~AudioCapture()
{
    stop();
}


//id: ""为默认设备
void AudioCapture::changeDevice(QString id)
{
    //停止綫程
    stop();
    deviceIdString = id;
    if(!start()){
        qDebug()<<"faile";
    }

}

bool AudioCapture::start()
{

    isCapture = true;
    return Initialize();
}



void AudioCapture::stop()
{

    SetEvent(stopSignal);
    isCapture = false;
    if(captureThr.joinable()){
        captureThr.join();
    }
    ResetEvent(stopSignal);

}

LPCWSTR AudioCapture::stringToLPCWSTR(std::string orig)//TOOD:newsize
{
    size_t origsize = orig.length() + 1;
    const size_t newsize = 100;
    size_t convertedChars = 0;
    wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length()-1));
    mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

    return wcstring;
}
/**
 * The speaker layout describes where the speakers are located in the room.
 * For OBS it dictates:
 *  *  how many channels are available and
 *  *  which channels are used for which speakers.
 *
 * Standard channel layouts where retrieved from ffmpeg documentation at:
 *     https://trac.ffmpeg.org/wiki/AudioChannelManipulation
 */
enum speaker_layout {
    SPEAKERS_UNKNOWN,     /**< Unknown setting, fallback is stereo. */
    SPEAKERS_MONO,        /**< Channels: MONO */
    SPEAKERS_STEREO,      /**< Channels: FL, FR */
    SPEAKERS_2POINT1,     /**< Channels: FL, FR, LFE */
    SPEAKERS_4POINT0,     /**< Channels: FL, FR, FC, RC */
    SPEAKERS_4POINT1,     /**< Channels: FL, FR, FC, LFE, RC */
    SPEAKERS_5POINT1,     /**< Channels: FL, FR, FC, LFE, RL, RR */
    SPEAKERS_7POINT1 = 8, /**< Channels: FL, FR, FC, LFE, RL, RR, SL, SR */
};

#define OBS_KSAUDIO_SPEAKER_4POINT1 \
    (KSAUDIO_SPEAKER_SURROUND | SPEAKER_LOW_FREQUENCY)
static speaker_layout ConvertSpeakerLayout(DWORD layout, WORD channels)
{
    switch (layout) {
    case KSAUDIO_SPEAKER_2POINT1:
        return SPEAKERS_2POINT1;
    case KSAUDIO_SPEAKER_SURROUND:
        return SPEAKERS_4POINT0;
    case OBS_KSAUDIO_SPEAKER_4POINT1:
        return SPEAKERS_4POINT1;
    case KSAUDIO_SPEAKER_5POINT1_SURROUND:
        return SPEAKERS_5POINT1;
    case KSAUDIO_SPEAKER_7POINT1_SURROUND:
        return SPEAKERS_7POINT1;
    }

    return (speaker_layout)channels;
}
static inline uint64_t convert_speaker_layout(enum speaker_layout layout)
{
    switch (layout) {
    case SPEAKERS_UNKNOWN:
        return 0;
    case SPEAKERS_MONO:
        return AV_CH_LAYOUT_MONO;
    case SPEAKERS_STEREO:
        return AV_CH_LAYOUT_STEREO;
    case SPEAKERS_2POINT1:
        return AV_CH_LAYOUT_SURROUND;
    case SPEAKERS_4POINT0:
        return AV_CH_LAYOUT_4POINT0;
    case SPEAKERS_4POINT1:
        return AV_CH_LAYOUT_4POINT1;
    case SPEAKERS_5POINT1:
        return AV_CH_LAYOUT_5POINT1_BACK;
    case SPEAKERS_7POINT1:
        return AV_CH_LAYOUT_7POINT1;
    }

    /* shouldn't get here */
    return 0;
}

bool AudioCapture::Initialize()
{
    HRESULT res;
    res = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr,
                           CLSCTX_ALL, __uuidof(IMMDeviceEnumerator),
                           (void **)enumerator.ReleaseAndGetAddressOf());
    if (FAILED(res)){
        //        throw ("Failed to create enumerator", res);
        qDebug()<<"ailed to create enumerator"<<QString("%1").arg(res,8,16,QLatin1Char('0')); //不足8位补0;
        abort();
        return false;
    }


    ////获取设备

    if(deviceIdString.isEmpty()){

        if(audioCaptureType == INPUTAUDIO){
            res = enumerator->GetDefaultAudioEndpoint( eCapture , eCommunications ,device.ReleaseAndGetAddressOf());
        }else{
            res = enumerator->GetDefaultAudioEndpoint( eRender , eConsole ,device.ReleaseAndGetAddressOf());

        }
        if (FAILED(res)){
            blog(LOG_INFO,"AudioCapture GetDefaultAudioEndpoint fail:lX",res);
            return false;
        }
    }else{
        LPCWSTR deviceId = stringToLPCWSTR(deviceIdString.toStdString());//设备id
        res = enumerator->GetDevice(deviceId, device.ReleaseAndGetAddressOf());
        if (FAILED(res)){
            blog(LOG_INFO,"AudioCapture GetDevice fail:lX,",res,deviceId);
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




    //初始化IAudioClient
    client.Reset();
    res = device->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr,
                           (void **)client.ReleaseAndGetAddressOf());
    if (FAILED(res)){
        //        throw HRError("Failed to activate client context", res);
        return false;

    }


    //获取格式
    struct DeleterWAVEFORMATEX
    {
        void operator()(WAVEFORMATEX *p)
        {
            CoTaskMemFree(p);
        }
    };
    std::unique_ptr<WAVEFORMATEX,DeleterWAVEFORMATEX> wfex;


    WAVEFORMATEX * wfexPtr = nullptr;
    res = client->GetMixFormat(&(wfexPtr));
    if (FAILED(res)){
        //        throw HRError("Failed to get mix format", res);
        return false;
    }
    wfex.reset(wfexPtr);
    int channels = wfexPtr->nChannels;
    int rate  =wfexPtr->nSamplesPerSec;

    DWORD layout = 0;

    if (wfex->wFormatTag == WAVE_FORMAT_EXTENSIBLE) {
        WAVEFORMATEXTENSIBLE *ext = (WAVEFORMATEXTENSIBLE *)wfexPtr;
        layout = ext->dwChannelMask;
    }

    /* WASAPI is always float */
    AVSampleFormat  format = AV_SAMPLE_FMT_FLT;
    auto  speakers = ConvertSpeakerLayout(layout,channels);
    uint64_t   ffmpegLayout =  convert_speaker_layout(speakers);
    //    get
    resamper->clearResampler();
    //    int64_t s = av_get_default_channel_layout(2);//3
    resamper->resamplerCreate(av_get_default_channel_layout(2),AV_SAMPLE_FMT_FLT,44100,ffmpegLayout,format,rate);//TODO

    DWORD flags = AUDCLNT_STREAMFLAGS_EVENTCALLBACK;
    if (audioCaptureType == OUTPUTAUDIO){
        flags |= AUDCLNT_STREAMFLAGS_LOOPBACK;
    }

    //#define BUFFER_TIME_100NS (5 * 10000000)
    //第三个参数  100ns为单位，1s=10000000
    res = client->Initialize(AUDCLNT_SHAREMODE_SHARED, flags,
                            0/* 5 * 10000000*/ /*BUFFER_TIME_100NS*/, 0, wfexPtr, nullptr);
    if (FAILED(res)){
        //        throw HRError("Failed to get initialize audio client", res);
        return false;
    }


    //    //没有声音时，在启动时会没有数据，
    //    /* Silent loopback fix. Prevents audio stream from stopping and */
    //    /* messing up timestamps and other weird glitches during silence */
    //    /* by playing a silent sample all over again.*/
    //    {

    //        std::unique_ptr<WAVEFORMATEX,DeleterWAVEFORMATEX> wfex;
    //        HRESULT res;
    //        LPBYTE buffer;
    //        UINT32 frames;
    //        ComPtr<IAudioClient> client;
    //        ComPtr<IAudioRenderClient> render;
    //        res = device->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr,
    //                               (void **)client.ReleaseAndGetAddressOf());
    //        if (FAILED(res)){
    //            //            throw HRError("Failed to activate client context", res);
    //            abort();

    //        }
    //        WAVEFORMATEX * wfexPtr = nullptr;
    //        res = client->GetMixFormat(&wfexPtr);
    //        if (FAILED(res)){
    //            //            throw HRError("Failed to get mix format", res);
    //            abort();
    //        }
    //        wfex.reset(wfexPtr);
    //        res = client->Initialize(AUDCLNT_SHAREMODE_SHARED, 0, 1000000/*BUFFER_TIME_100NS*/,
    //                                 0, wfexPtr, nullptr);
    //        if (FAILED(res)){
    //            //            throw HRError("Failed to get initialize audio client", res);
    //            abort();
    //        }

    //        res = client->GetBufferSize(&frames);
    //        if (FAILED(res)){
    //            //            throw HRError("Failed to get buffer size", res);
    //            abort();
    //        }
    //        res = client->GetService(__uuidof(IAudioRenderClient),
    //                                 (void **)render.ReleaseAndGetAddressOf());
    //        if (FAILED(res)){
    //            //            throw HRError("Failed to get render client", res);
    //            abort();
    //        }
    //        res = render->GetBuffer(frames, &buffer);
    //        if (FAILED(res)){
    //            //            throw HRError("Failed to get buffer", res);
    //            abort();
    //        }
    //        memset(buffer, 0, frames * wfex->nBlockAlign);

    //        render->ReleaseBuffer(frames, 0);
    //    }




    //初始化IAudioCaptureClient
    res = client->GetService(__uuidof(IAudioCaptureClient),
                             (void **)capture.ReleaseAndGetAddressOf());
    if (FAILED(res)){
        //        throw HRError("Failed to create capture context", res);
        return false;
    }
    res = client->SetEventHandle(receiveSignal);
    if (FAILED(res)){
        qDebug()<<"faile";

        return false;
    }else{
        //        throw HRError("Failed to set event handle", res);

        //        captureThread = CreateThread(nullptr, 0, WASAPISource::CaptureThread,
        //                                     this, 0, nullptr);
        //        if (!captureThread.Valid())
        //            throw "Failed to create capture thread";

        //        active = true;

        //        blog(LOG_INFO, "WASAPI: Device '%s' [%s Hz] initialized",
        //             device_name.c_str(), device_sample.c_str());


        auto thr = std::thread(&AudioCapture::captureThread,this);
        captureThr = std::move(thr);
        client->Start();
        return  true;
    }

}

bool AudioCapture::WaitForCaptureSignal(DWORD numSignals, const HANDLE *sigs,
                                        DWORD duration)
{
    DWORD ret;
    ret = WaitForMultipleObjects(numSignals, sigs, false, INFINITE/*duration*/);//一直等待信号

    return ret == WAIT_OBJECT_0 || ret == WAIT_TIMEOUT;
}

void AudioCapture::captureThread()
{
    //    /* Output devices don't signal, so just make it check every 10 ms */
    //#define RECONNECT_INTERVAL 3000
    //DWORD dur = source->isInputDevice ? RECONNECT_INTERVAL : 10;
    DWORD dur =10;
    HANDLE sigs[2] = {receiveSignal, stopSignal};

    //    os_set_thread_name("win-wasapi: capture thread");


    while (WaitForCaptureSignal(2, sigs, dur)) {
        if (!processCaptureData()) {
            //            reconnect = true;
            break;
        }
    }


    client->Stop();
}

bool AudioCapture::processCaptureData()
{
    HRESULT res;
    LPBYTE buffer;
    UINT32 frames;
    DWORD flags;
    uint64_t pos, ts;
    UINT captureSize = 0;

    //    while (isCapture) {//TODO:  采用發信號取數據
    res = capture->GetNextPacketSize(&captureSize);

    if (FAILED(res)) {
        if (res != AUDCLNT_E_DEVICE_INVALIDATED){
            blog(LOG_WARNING,
                 "[WASAPISource::GetCaptureData]"
                 " capture->GetNextPacketSize"
                 " failed: %lX",
                 res);
        }
        return false;
    }

    if (!captureSize){
        //            break;
        return true;
    }

    static uint64_t  pre = 0;
    static uint64_t  prePos = 0;
    res = capture->GetBuffer(&buffer, &frames, &flags, &pos, &ts);
    if (FAILED(res)) {
        if (res != AUDCLNT_E_DEVICE_INVALIDATED){
            blog(LOG_WARNING,
                 "[WASAPISource::GetCaptureData]"
                 " capture->GetBuffer"
                 " failed: %lX",
                 res);
        }
        return false;
    }
//    //TODO:这之后时间耗时会有问题。
//    Sleep(10000);
//    qDebug()<<pos<<ts<<ts-pre<<pos-prePos<<frames;
    pre =  ts;
    prePos = pos;
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

    //重采样

    uint8_t * data = nullptr;
    uint32_t dataFrames = 0;
    uint64_t  tsOffset = 0;

    const uint8_t* inData  = buffer;
    resamper->resample(&data, &dataFrames ,&tsOffset,&inData,frames);

    if(onAudioData){
        onAudioData(data,dataFrames);
        av_free(data);
    }

    capture->ReleaseBuffer(frames);
    //}

    return true;
}



