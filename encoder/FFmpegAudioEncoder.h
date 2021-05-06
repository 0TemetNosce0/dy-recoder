#pragma once

extern "C"{
#include <libavutil/opt.h>
#include <libavformat/avformat.h>
}
#define MAX_AV_PLANES 8

class FFmpegAudioEncoder
{
public:
    FFmpegAudioEncoder();
    ~FFmpegAudioEncoder();

    void  init();

    bool encode();

    void popEncoderPacket();
private:
    AVCodec *codec = nullptr;
    AVCodecContext *context = nullptr;
    uint8_t *samples[MAX_AV_PLANES];
    AVFrame *aframe;
    int64_t total_samples;

    size_t audio_planes;
    size_t audio_size;

    int frame_size; /* pretty much always 1024 for AAC */
    int frame_size_bytes;


};

