#pragma once

extern "C"{

//#include <libavutil/avutil.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
}

class AudioResampler
{
public:
    AudioResampler();
    ~AudioResampler();
    void resamplerCreate(int64_t out_ch_layout, enum AVSampleFormat out_sample_fmt, int out_sample_rate,
                         int64_t  in_ch_layout, enum AVSampleFormat  in_sample_fmt, int  in_sample_rate);

    void clearResampler();
    bool resample(uint8_t **output, uint32_t *out_frames, uint64_t *ts_offset, const uint8_t ** const input, uint32_t in_frames);
private:
    SwrContext *context = nullptr;

    int inSampleRate =0;
    int outputSampleRate = 0;
    AVSampleFormat output_format;
    int output_ch;
};

