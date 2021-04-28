#pragma once

#include "WASAPIAudioDevices.h"

//#include <Audioclient.h>
#include <functional>
#include <future>
//#include <mmdeviceapi.h>
#include <QDebug>

#pragma pack(push, 1)
class S24 {
protected:
    unsigned char c3[3];

public:
    S24() {}

    S24 &operator=(const int &i) {
        c3[0] = (i & 0x000000ff);
        c3[1] = (i & 0x0000ff00) >> 8;
        c3[2] = (i & 0x00ff0000) >> 16;
        return *this;
    }

    S24(const double &d) { *this = (int) d; }
    S24(const float &f) { *this = (int) f; }
    S24(const signed short &s) { *this = (int) s; }
    S24(const char &c) { *this = (int) c; }

    int asInt() {
        int i = c3[0] | (c3[1] << 8) | (c3[2] << 16);
        if (i & 0x800000)
            i |= ~0xffffff;
        return i;
    }
};
#pragma pack(pop)


struct CoreAudio;
class WASAPIAudioRecoder {
public:
    WASAPIAudioRecoder();
    ~WASAPIAudioRecoder();
    QVector<AudioDeviceInfo> getInputDevice();
    std::function<void(char *data, uint32_t size)> callback = nullptr;
    bool wasapiThread();
    bool stopFlag = false;
    std::future<bool> future;

    std::vector<float> buffer;
    uint bufferCount = 0;
    uint maxBufferCount = 0;
    AudioDeviceInfo curDeviceInfo;
    bool start(AudioDeviceInfo device);
    void stop();

    //     IAudioSessionManager*        m_AudioSessionManager = NULL;
    //     IAudioSessionControl*        m_AudioSessionControl    = NULL;

    uint getRecoderChannel() const;

    uint getRecoderSampleRate() const;

    typedef unsigned long RtAudioFormat;
    static const RtAudioFormat RTAUDIO_SINT8 = 0x1;    // 8-bit signed integer.
    static const RtAudioFormat RTAUDIO_SINT16 = 0x2;   // 16-bit signed integer.
    static const RtAudioFormat RTAUDIO_SINT24 = 0x4;   // 24-bit signed integer.
    static const RtAudioFormat RTAUDIO_SINT32 = 0x8;   // 32-bit signed integer.
    static const RtAudioFormat RTAUDIO_FLOAT32 = 0x10; // Normalized between plus/minus 1.0.
    static const RtAudioFormat RTAUDIO_FLOAT64 = 0x20; // Normalized between plus/minus 1.0.
    enum AudioFormat {
        AUDIO_NO = 0x01,
        AUDIO_SINT8 = 0x1,    // 8-bit signed integer.
        AUDIO_SINT16 = 0x2,   // 16-bit signed integer.
        AUDIO_SINT24 = 0x4,   // 24-bit signed integer.
        AUDIO_SINT32 = 0x8,   // 32-bit signed integer.
        AUDIO_FLOAT32 = 0x10, // Normalized between plus/minus 1.0.
        AUDIO_FLOAT64 = 0x20, // Normalized between plus/minus 1.0.
    };

private:

    CoreAudio *coreAudio = nullptr;

    void releaseAudio();

    uint recoderChannel = 0;
    uint recoderSampleRate = 0;
    AudioFormat recoderFormat = AUDIO_NO;
    //format:float;

    typedef S24 Int24;
    typedef signed short Int16;
    typedef signed int Int32;
    typedef float Float32;
    typedef double Float64;
    void ConvertBuffer(char *inBuffer, int size); //size:采样个数
};
