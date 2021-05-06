#pragma once
#include <stdint.h>

struct PaStreamParameters;
typedef void PaStream;

class AudioOutputPortAudio
{
public:
    AudioOutputPortAudio();
    ~AudioOutputPortAudio();
    inline bool isOpen()
    {
        return (stream != nullptr);
    }

    bool open(int chn, int sampleRate,int deviceIndex =-1);
    bool close();
    bool pause();

    bool write(uint8_t *buffer, const uint32_t size);
    bool clear();

    double getSuggestedLatency() const;//返回延时
private:
    PaStreamParameters *outputParameters = nullptr;
    PaStream *stream = nullptr;
    bool initialized = false;
};

