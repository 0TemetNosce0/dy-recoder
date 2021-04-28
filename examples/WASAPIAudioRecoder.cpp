
#include "WASAPIAudioRecoder.h"
#include <Audioclient.h>
#include <mmdeviceapi.h>
#include <QDebug>

#define SAFE_RELEASE(punk) \
    if ((punk) != NULL) { \
        (punk)->Release(); \
        (punk) = NULL; \
    }
//const CLSID __uuidof(MMDeviceEnumerator) = __uuidof(MMDeviceEnumerator);
//const IID __uuidof(IMMDeviceEnumerator) = __uuidof(IMMDeviceEnumerator);
//const IID __uuidof(IAudioClient) = __uuidof(IAudioClient);
//const IID __uuidof(IAudioCaptureClient) = __uuidof(IAudioCaptureClient);
struct CoreAudio
{
    IMMDeviceEnumerator *pEnumerator = nullptr;
    IMMDevice *pDevice = nullptr;
    IAudioClient *pAudioClient = nullptr;
    IAudioCaptureClient *pCaptureClient = nullptr;
    WAVEFORMATEX *pwfx = nullptr;
    HANDLE hAudioSamplesReadyEvent = nullptr;
};

WASAPIAudioRecoder::WASAPIAudioRecoder() {
    buffer.resize(2 * 4410);
    //    //
    HRESULT hr;
    hr = CoInitialize(nullptr);
    if (FAILED(hr)) {
        qDebug("Unable to initialize COM in thread: %x\n", hr);
        //        return false;
    }
    coreAudio = new CoreAudio;
}

WASAPIAudioRecoder::~WASAPIAudioRecoder() {
    CoUninitialize();
}

QVector<AudioDeviceInfo> WASAPIAudioRecoder::getInputDevice() {
    WASAPIAudioDevices devices;

    QVector<AudioDeviceInfo> vec;
    devices.GetWASAPIAudioDevices(vec, true);
    return vec;
}

bool WASAPIAudioRecoder::wasapiThread() {
    HRESULT hr;
    //SetEventHandle
    coreAudio->hAudioSamplesReadyEvent = CreateEventEx(NULL,
                                                       NULL,
                                                       0,
                                                       EVENT_MODIFY_STATE | SYNCHRONIZE);
    //      captureEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (!coreAudio->hAudioSamplesReadyEvent) {
        //            errorType = RtAudioError::SYSTEM_ERROR;
        //        qDebug("RtApiWasapi::wasapiThread: Unable to create capture event.");

        qDebug("Unable to create samples ready event: %d.\n", GetLastError());
        releaseAudio();
        return false;
    }

    hr = coreAudio->pAudioClient->SetEventHandle(coreAudio->hAudioSamplesReadyEvent);
    if (FAILED(hr)) {
        qDebug("RtApiWasapi::wasapiThread: Unable to set capture event handle.");
        releaseAudio();
        return false;
    }

    // 创建采集管理接口IAudioCaptureClient
    hr = coreAudio->pAudioClient->GetService(__uuidof(IAudioCaptureClient),
                                             (void **) &coreAudio->pCaptureClient);
    if (FAILED(hr)) {
        qDebug("RtApiWasapi::wasapiThread: Unable to retrieve capture client handle.");
        releaseAudio();
        return false;
    }

    //    hr = pAudioClient->Reset();
    //    if (FAILED(hr)) {
    //        qDebug("RtApiWasapi::wasapiThread: Unable to reset capture stream.");
    //        goto Exit;
    //    }

    hr = coreAudio->pAudioClient->Start(); // Start recording.

    HANDLE waitArray[3];
    waitArray[0] = coreAudio->hAudioSamplesReadyEvent;

    //    bool stillPlaying = true;

    UINT32 packetLength = 0;
    BYTE *pData;
    DWORD flags;
    UINT32 numFramesAvailable;

    while (!stopFlag) {
        //TODO:一直等下去?
        DWORD waitResult = WaitForMultipleObjects(1, waitArray, FALSE, INFINITE);
        switch (waitResult) {
        case WAIT_OBJECT_0 + 0: // _AudioSamplesReadyEvent
            hr = coreAudio->pCaptureClient->GetNextPacketSize(&packetLength);
            if (FAILED(hr)) {
                qDebug("GetNextPacketSize falie");
                releaseAudio();
                return false;
            }
            while (packetLength != 0) {
                // Get the available data in the shared buffer.
                // 锁定缓冲区，获取数据
                hr = coreAudio->pCaptureClient->GetBuffer(&pData,
                                                          &numFramesAvailable,
                                                          &flags,
                                                          NULL,
                                                          NULL);
                if (FAILED(hr)) {
                    qDebug("Audio capture GetBuffer fail");
                    releaseAudio();
                    return false;
                }

                //                                qDebug() << "sssssssssssss"<<packetLength<<numFramesAvailable;
                //                if (flags & AUDCLNT_BUFFERFLAGS_SILENT) { //静音
                //                    qDebug() << "AUDCLNT_BUFFERFLAGS_SILENT";
                //                    pData = NULL; // Tell CopyData to write silence.
                //                }

                //                //转换format;
                //                if (!pData) {
                //                    buffer.at(0) = 0;
                //                    buffer.at(1) = 0;
                //                    bufferCount = 0;
                //                    if (callback) {
                //                        callback(reinterpret_cast<char *>(buffer.data()), 1);
                //                    }
                //                } else {
                ConvertBuffer((char *) pData, numFramesAvailable);
                //                }
                if (flags & AUDCLNT_BUFFERFLAGS_DATA_DISCONTINUITY) {
                    qDebug("%06d # AUDCLNT_BUFFERFLAGS_DATA_DISCONTINUITY \n", 1 /*nCnt*/);
                }

                hr = coreAudio->pCaptureClient->ReleaseBuffer(numFramesAvailable);
                if (FAILED(hr)) {
                    qDebug("ReleaseBuffer fail");
                }
                hr = coreAudio->pCaptureClient->GetNextPacketSize(&packetLength);
                if (FAILED(hr)) {
                    qDebug("GetNextPacketSize fail");
                }
                //                // test GetCurrentPadding
                //                //////////////////////////////////////////////////////////////////////////
                //                /*
                //                    This method retrieves a padding value that indicates the amount of
                //                    valid, unread data that the endpoint buffer currently contains.
                //                    返回buffer中合法的未读取的数据大小。
                //                    The padding value is expressed as a number of audio frames.
                //                    The size in bytes of an audio frame equals
                //                    the number of channels in the stream multiplied by the sample size per channel.
                //                    For example, the frame size is four bytes for a stereo (2-channel) stream with 16-bit samples.
                //                    The padding value的单位是audio frame。
                //                    一个audio frame的大小等于 通道数 * 每个通道的sample大小。
                //                    For a shared-mode capture stream, the padding value reported by GetCurrentPadding
                //                    specifies the number of frames of capture data
                //                    that are available in the next packet in the endpoint buffer.
                //                    */
                //                UINT32 ui32NumPaddingFrames;
                //                hr = pAudioClient->GetCurrentPadding(&ui32NumPaddingFrames);
                //                EXIT_ON_ERROR(hr)
                //                if (0 != ui32NumPaddingFrames) {
                //                    printf("GetCurrentPadding : %6u\n", ui32NumPaddingFrames);
                //                }

            } // end of 'while (packetLength != 0)'

            break;
        } // end of 'switch (waitResult)'

    } // end of 'while (stillPlaying)'

    hr = coreAudio->pAudioClient->Stop(); // Stop recording.
    if (FAILED(hr)) {
        qDebug("IAudioClient stop fail");
    }
    return false;
}

bool WASAPIAudioRecoder::start(AudioDeviceInfo device) {
    stopFlag = false;
    curDeviceInfo = device;
    bufferCount = 0;
    HRESULT hr;
    // 枚举音频设备
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),
                          NULL,
                          CLSCTX_ALL,
                          __uuidof(IMMDeviceEnumerator),
                          (void **) &coreAudio->pEnumerator);
    if (hr == S_OK) {
        qDebug("CoCreateInstance success!");
    } else {
        qDebug("CoCreateInstance faile!");
    }
    //获取默认设备
    hr = coreAudio->pEnumerator
             ->GetDefaultAudioEndpoint(eCapture,
                                       eConsole,
                                       &coreAudio->pDevice); //eCaptures输入,eRender输出
    if (FAILED(hr)) {
        qDebug("RtApiWasapi::getDeviceInfo: Unable to retrieve default capture device handle.");

        return false;
    }

    IMMDeviceCollection *captureDevices = NULL;
    hr = coreAudio->pEnumerator->EnumAudioEndpoints(eCapture, DEVICE_STATE_ACTIVE, &captureDevices);
    if (FAILED(hr)) {
        qDebug("EnumAudioEndpoints fail");
        releaseAudio();
        return false;
    }
    unsigned int captureDeviceCount = 0;
    hr = captureDevices->GetCount(&captureDeviceCount);
    if (FAILED(hr)) {
        qDebug("Unable to retrieve capture device count.");
        releaseAudio();
        return false;
    }
    for (uint i = 0; i < captureDeviceCount; i++) {
        IMMDevice *devicePtr = nullptr;
        hr = captureDevices->Item(i, &devicePtr);
        if (FAILED(hr)) {
            qDebug("Unable to retrieve capture device handle.");

        } else {
            LPWSTR ppstrId = nullptr;
            devicePtr->GetId(&ppstrId);
            QString strId;
            strId = QString::fromStdWString(ppstrId == nullptr ? L"" : ppstrId);
            if (strId == curDeviceInfo.id) {
                coreAudio->pDevice = devicePtr;
                break;
            }
        }
        SAFE_RELEASE(devicePtr)
    }
    if (!coreAudio->pDevice) {
        qDebug("capture device null");
        releaseAudio();
        return false;
    }
    //    // 得到音频会话接口IAudioSessionManager
    //    hr = pDevice->Activate(__uuidof(m_AudioSessionManager), CLSCTX_ALL, NULL, (void**)&m_AudioSessionManager);
    //    if (FAILED(hr)) {
    //        qDebug("11111111");
    //    }

    //    // 设置会话(Session)参数
    //    hr = m_AudioSessionManager->GetAudioSessionControl(NULL,0,&m_AudioSessionControl);
    //    if (FAILED(hr)) {
    //        qDebug("11111111");
    //    }

    //    // 设置声音改变参数通知
    //    CMutedSessionEvents *m_pMutedSessionEvents = new CMutedSessionEvents();
    //    hr = m_AudioSessionControl->RegisterAudioSessionNotification(m_pMutedSessionEvents);
    //    if (FAILED(hr)) {
    //        qDebug("11111111");
    //    }

    // 创建一个管理对象，通过它可以获取到你需要的一切数据
    hr = coreAudio->pDevice->Activate(__uuidof(IAudioClient),
                                      CLSCTX_ALL,
                                      NULL,
                                      (void **) &coreAudio->pAudioClient);
    if (FAILED(hr)) {
        qDebug("Unable to retrieve render device audio client.");
        releaseAudio();
        return false;
    }
    hr = coreAudio->pAudioClient->GetMixFormat(&coreAudio->pwfx);
    if (FAILED(hr)) {
        qDebug(" Unable to retrieve render device mix format.");
        releaseAudio();
        return false;
    }

    qDebug("\nGetMixFormat...");
    qDebug() << "wFormatTag      : " << coreAudio->pwfx->wFormatTag;
    qDebug() << "nChannels       : " << coreAudio->pwfx->nChannels;
    qDebug() << "nSamplesPerSec  : " << coreAudio->pwfx->nSamplesPerSec;
    qDebug() << "nAvgBytesPerSec : " << coreAudio->pwfx->nAvgBytesPerSec;
    qDebug() << "nBlockAlign     : " << coreAudio->pwfx->nBlockAlign;
    qDebug() << "wBitsPerSample  : " << coreAudio->pwfx->wBitsPerSample;
    qDebug() << "cbSize          : " << coreAudio->pwfx->cbSize;

    recoderChannel = coreAudio->pwfx->nChannels;
    recoderSampleRate = coreAudio->pwfx->nSamplesPerSec;
    maxBufferCount = recoderSampleRate / 10; //100ms
    buffer.resize(recoderChannel * maxBufferCount);
    // native format
    recoderFormat = AUDIO_NO;
    if (coreAudio->pwfx->wFormatTag == WAVE_FORMAT_IEEE_FLOAT
        || (coreAudio->pwfx->wFormatTag == WAVE_FORMAT_EXTENSIBLE
            && ((WAVEFORMATEXTENSIBLE *) coreAudio->pwfx)->SubFormat
                   == KSDATAFORMAT_SUBTYPE_IEEE_FLOAT)) {
        if (coreAudio->pwfx->wBitsPerSample == 32) {
            recoderFormat = AUDIO_FLOAT32;
        } else if (coreAudio->pwfx->wBitsPerSample == 64) {
            recoderFormat = AUDIO_FLOAT64;
        }
    } else if (coreAudio->pwfx->wFormatTag == WAVE_FORMAT_PCM
               || (coreAudio->pwfx->wFormatTag == WAVE_FORMAT_EXTENSIBLE
                   && ((WAVEFORMATEXTENSIBLE *) coreAudio->pwfx)->SubFormat
                          == KSDATAFORMAT_SUBTYPE_PCM)) {
        if (coreAudio->pwfx->wBitsPerSample == 8) {
            recoderFormat = AUDIO_SINT8;
        } else if (coreAudio->pwfx->wBitsPerSample == 16) {
            recoderFormat = AUDIO_SINT16;
        } else if (coreAudio->pwfx->wBitsPerSample == 24) {
            recoderFormat = AUDIO_SINT24;
        } else if (coreAudio->pwfx->wBitsPerSample == 32) {
            recoderFormat = AUDIO_SINT32;
        }
    }

    hr = coreAudio->pAudioClient->Initialize(AUDCLNT_SHAREMODE_SHARED,
                                             AUDCLNT_STREAMFLAGS_EVENTCALLBACK
                                                 | AUDCLNT_STREAMFLAGS_NOPERSIST,
                                             0 /*hnsRequestedDuration*/,
                                             0,
                                             coreAudio->pwfx,
                                             NULL);

    if (FAILED(hr)) {
        qDebug("RtApiWasapi::wasapiThread: Unable to initialize capture audio client.");
        releaseAudio();
        return false;
    }

    //    REFERENCE_TIME hnsStreamLatency;
    //    hr = pAudioClient->GetStreamLatency(&hnsStreamLatency);//获取当前流的最大延迟

    //    REFERENCE_TIME hnsDefaultDevicePeriod;
    //    REFERENCE_TIME hnsMinimumDevicePeriod;
    //    hr = pAudioClient->GetDevicePeriod(&hnsDefaultDevicePeriod, &hnsMinimumDevicePeriod);

    UINT32 bufferFrameCount;
    hr = coreAudio->pAudioClient->GetBufferSize(
        &bufferFrameCount); //这个buffersize，指的是缓冲区最多可以存放多少帧的数据量
    if (FAILED(hr)) {
        qDebug("RtApiWasapi::wasapiThread: Unable to retrieve render buffer size.");
        releaseAudio();
        return false;
    }

    future = std::async(std::launch::async, &WASAPIAudioRecoder::wasapiThread, this);

    return true;
}

void WASAPIAudioRecoder::stop() {
    if (!stopFlag) {
        stopFlag = true;
        if (future.valid()) {
            future.get();
        }
    }
}

void WASAPIAudioRecoder::releaseAudio() {
    //    CoTaskMemFree(pwfx);
    //    SAFE_RELEASE(pEnumerator)
    //    SAFE_RELEASE(pDevice)
    //    SAFE_RELEASE(pAudioClient)
    //    SAFE_RELEASE(pCaptureClient)
}

uint WASAPIAudioRecoder::getRecoderSampleRate() const {
    return recoderSampleRate;
}

uint WASAPIAudioRecoder::getRecoderChannel() const {
    return recoderChannel;
}

//duplex device?
void WASAPIAudioRecoder::ConvertBuffer(char *inBuffer, int size) {
    // This function does format conversion, input/output channel compensation, and
    // data interleaving/deinterleaving.  24-bit integers are assumed to occupy
    // the lower three bytes of a 32-bit integer.

    //    // Clear our device buffer when in/out duplex device channels are different
    //    if (outBuffer == stream_.deviceBuffer && stream_.mode == DUPLEX
    //        && (stream_.nDeviceChannels[0] < stream_.nDeviceChannels[1]))
    //        memset(outBuffer, 0, size * recoderChannel * formatBytes(info.outFormat));

    int j;
    if (1 /*info.outFormat == RTAUDIO_FLOAT32*/) { //float
        Float32 scale;
        //        Float32 *out = (Float32 *) outBuffer;

        if (recoderFormat == AUDIO_SINT8) {
            signed char *in = (signed char *) inBuffer;
            scale = (Float32)(1.0 / 127.5);
            for (unsigned int i = 0; i < size; i++) {
                for (j = 0; j < recoderChannel; j++) {
                    uint bufferIndex = bufferCount * recoderChannel + j;
                    buffer[bufferIndex] = (Float32) in[j];
                    buffer[bufferIndex] += 0.5;
                    buffer[bufferIndex] *= scale;
                }
                in += recoderChannel;
                bufferCount++;
                if (bufferCount == maxBufferCount) {
                    if (callback) {
                        callback(reinterpret_cast<char *>(buffer.data()), maxBufferCount);
                    }
                    bufferCount = 0;
                } else {
                }
            }
        } else if (recoderFormat == AUDIO_SINT16) {
            Int16 *in = (Int16 *) inBuffer;
            scale = (Float32)(1.0 / 32767.5);

            for (unsigned int i = 0; i < size; i++) {
                for (j = 0; j < recoderChannel; j++) {
                    uint bufferIndex = bufferCount * recoderChannel + j;

                    buffer[bufferIndex] = (Float32) in[j];
                    buffer[bufferIndex] += 0.5;
                    buffer[bufferIndex] *= scale;
                }
                in += recoderChannel;
                bufferCount++;
                if (bufferCount == maxBufferCount) {
                    if (callback) {
                        callback(reinterpret_cast<char *>(buffer.data()), maxBufferCount);
                    }
                    bufferCount = 0;
                } else {
                }
            }
        } else if (recoderFormat == AUDIO_SINT24) {
            Int24 *in = (Int24 *) inBuffer;
            scale = (Float32)(1.0 / 8388607.5);
            for (unsigned int i = 0; i < size; i++) {
                for (j = 0; j < recoderChannel; j++) {
                    uint bufferIndex = bufferCount * recoderChannel + j;
                    buffer[bufferIndex] = (Float32)(in[j].asInt());
                    buffer[bufferIndex] += 0.5;
                    buffer[bufferIndex] *= scale;
                }
                in += recoderChannel;
                bufferCount++;
                if (bufferCount == maxBufferCount) {
                    if (callback) {
                        callback(reinterpret_cast<char *>(buffer.data()), maxBufferCount);
                    }
                    bufferCount = 0;
                } else {
                }
            }
        } else if (recoderFormat == AUDIO_SINT32) {
            Int32 *in = (Int32 *) inBuffer;
            scale = (Float32)(1.0 / 2147483647.5);
            for (unsigned int i = 0; i < size; i++) {
                for (j = 0; j < recoderChannel; j++) {
                    uint bufferIndex = bufferCount * recoderChannel + j;

                    buffer[bufferIndex] = (Float32) in[j];
                    buffer[bufferIndex] += 0.5;
                    buffer[bufferIndex] *= scale;
                }
                in += recoderChannel;
                bufferCount++;
                if (bufferCount == maxBufferCount) {
                    if (callback) {
                        callback(reinterpret_cast<char *>(buffer.data()), maxBufferCount);
                    }
                    bufferCount = 0;
                } else {
                }
            }
        } else if (recoderFormat == AUDIO_FLOAT32) {
            // Channel compensation and/or (de)interleaving only.
            Float32 *in = (Float32 *) inBuffer;
            for (unsigned int i = 0; i < size; i++) {
                for (j = 0; j < recoderChannel; j++) {
                    uint bufferIndex = bufferCount * recoderChannel + j;

                    buffer[bufferIndex] = in[j];
                }
                in += recoderChannel;
                bufferCount++;
                if (bufferCount == maxBufferCount) {
                    if (callback) {
                        callback(reinterpret_cast<char *>(buffer.data()), maxBufferCount);
                    }
                    bufferCount = 0;
                } else {
                }
            }
        } else if (recoderFormat == AUDIO_FLOAT64) {
            Float64 *in = (Float64 *) inBuffer;
            for (unsigned int i = 0; i < size; i++) {
                for (j = 0; j < recoderChannel; j++) {
                    uint bufferIndex = bufferCount * recoderChannel + j;

                    buffer[bufferIndex] = (Float32) in[j];
                }
                in += recoderChannel;
                bufferCount++;
                if (bufferCount == maxBufferCount) {
                    if (callback) {
                        callback(reinterpret_cast<char *>(buffer.data()), maxBufferCount);
                    }
                    bufferCount = 0;
                } else {
                }
            }
        }
    }
}
