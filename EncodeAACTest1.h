#pragma once

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/opt.h"
#include "libswresample/swresample.h"
};
#include <vector>

class EncodeAACTest1 {
public:
    EncodeAACTest1();
    int init();
    void end();
 void encode(uint8_t *data, size_t size);
    //编码
    AVCodec *encode_codec = nullptr;
    AVCodecContext *encode_context = nullptr;

    uint8_t *samples[8];
    AVFrame *aframe;
    int64_t total_samples;

    size_t audio_planes;
    size_t audio_size = 4;

    int frame_size = 0;       /* pretty much always 1024 for AAC */
    int frame_size_bytes = 0; //frame的大小；
    std::vector<uint8_t> packet_buffer;
    size_t packet_bufferStartPos = 0;
    size_t packet_bufferSize = 0;

    //write packet


    AVFormatContext *format_context;
    AVOutputFormat *format;
    AVStream *audio_stream;
};
