//#pragma once
//extern "C" {
//#include "libavcodec/avcodec.h"
//#include "libavformat/avformat.h"
//#include "libavutil/opt.h"
//#include "libswresample/swresample.h"
//};
//#include <vector>
//class EncodeAACTest {
//public:
//    EncodeAACTest();
//    int init();
//    bool initialize_codec();
//    void encode(uint8_t *data, size_t size);
//    bool enc_create();
//    void end();
//    int init1(); //文件中获取信息
//    int init2(); //传入信息
//    int init_avformat();
//    //编码
//    AVCodec *encode_codec = nullptr;
//    AVCodecContext *encode_context = nullptr;

//    uint8_t *samples[8];
//    AVFrame *aframe;
//    int64_t total_samples;

//    size_t audio_planes;
//    size_t audio_size = 4;

//    int frame_size = 0;       /* pretty much always 1024 for AAC */
//    int frame_size_bytes = 0; //frame的大小；
//    std::vector<uint8_t> packet_buffer;
//    size_t packet_bufferStartPos = 0;
//    size_t packet_bufferSize = 0;
//    //write packet
//    struct main_params {
//        char *file;
//        /* printable_file is file with any stream key information removed */
////        struct dstr printable_file;
//        int has_video;
//        int tracks;
//        char *vcodec;
//        int vbitrate;
//        int gop;
//        int width;
//        int height;
//        int fps_num;
//        int fps_den;
//        int color_primaries;
//        int color_trc;
//        int colorspace;
//        int color_range;
//        char *acodec;
//        char *muxer_settings;
//    };
//    struct audio_params {
//        char *name;
//        int abitrate;
//        int sample_rate;
//        int channels;
//    };

//    struct header {
//        uint8_t *data;
//        int size;
//    };

//    struct audio_info {
//        AVStream *stream;
//        AVCodecContext *ctx;
//    };
//    struct ffmpeg_mux {
//        AVFormatContext *output;
//        AVStream *video_stream;
//        AVCodecContext *video_ctx;
//        struct audio_info *audio_infos;
//        struct main_params params;
//        struct audio_params *audio;
//        struct header video_header;
//        struct header *audio_header;
//        int num_audio_streams;
//        bool initialized;
//        char error[4096];
//    };
//    struct ffmpeg_mux    * ffm = {0};
//char *file = "d:/tdjm.aac";
//        char * audio_params_name = ;
//        int  audio_params_abitrate = 64000;
//        int  audio_params_sample_rate = 44100;
//        int  audio_params_channels  =2;

//        AVCodecContext *audio_mux_ctx;

//        AVFormatContext * audio_mux_format_context;
//        AVStream *audio_mux_stream;
////    AVFormatContext *pFormatCtx = nullptr;
////    AVOutputFormat *fmt = nullptr;
////    AVStream *audio_st = nullptr;
//};
