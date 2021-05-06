#include "FFmpegAudioEncoder.h"
#include <QDebug>
FFmpegAudioEncoder::FFmpegAudioEncoder()
{

}

FFmpegAudioEncoder::~FFmpegAudioEncoder()
{

}

void FFmpegAudioEncoder::init()
{
//    const char *type;
//    const char *alt;
//    int bitrate;
//    codec = avcodec_find_encoder_by_name(type);
//    if (!codec && alt) {
//        codec = avcodec_find_encoder_by_name(alt);
////        type = alt;
//    }

//    if (!codec) {
//        qFatal("Couldn't find encoder");
//        goto fail;
//    }
//    if (!bitrate) {
//        qFatal("Invalid bitrate specified");
//        return ;
//    }

//    context = avcodec_alloc_context3(codec);
//    if (!context) {
//        qFatal("Failed to create codec context");
//        goto fail;
//    }

//    context->bit_rate = bitrate * 1000;
//    const struct audio_output_info *aoi;

//    context->channels = (int)audio_output_get_channels(audio);
//    context->channel_layout =0;
//    context->sample_rate = 0;
//    context->sample_fmt = codec->sample_fmts
//                                   ? codec->sample_fmts[0]
//                                   : AV_SAMPLE_FMT_FLTP;


//    /* check to make sure sample rate is supported */
//    if (codec->supported_samplerates) {
//        const int *rate = codec->supported_samplerates;
//        int cur_rate = context->sample_rate;
//        int closest = 0;

//        while (*rate) {
//            int dist = abs(cur_rate - *rate);
//            int closest_dist = abs(cur_rate - closest);

//            if (dist < closest_dist)
//                closest = *rate;
//            rate++;
//        }

//        if (closest)
//            context->sample_rate = closest;
//    }

//    av_opt_set(context->priv_data, "aac_coder", "fast", 0);

////    audio_planes = get_audio_planes(format, aoi->speakers);
////    audio_size = get_audio_size(format, aoi->speakers, 1);

////    info("bitrate: %" PRId64 ", channels: %d, channel_layout: %x\n",
////         (int64_t)context->bit_rate / 1000,
////         (int)context->channels,
////         (unsigned int)context->channel_layout);


//    /* enable experimental FFmpeg encoder if the only one available */
//    context->strict_std_compliance = -2;

//    context->flags = AV_CODEC_FLAG_GLOBAL_HEADER;


//    //initialize_codec
//    int ret;

//    aframe = av_frame_alloc();
//    if (!aframe) {
//        qWarning("Failed to allocate audio frame");
//        return ;
//    }

//    ret = avcodec_open2(context, codec, NULL);
//    if (ret < 0) {
////        struct dstr error_message = {0};
////        dstr_printf(&error_message, "Failed to open AAC codec: %s",
////                    av_err2str(ret));
////        obs_encoder_set_last_error(encoder, error_message.array);
////        dstr_free(&error_message);
//        qWarning("Failed to open AAC codec: %s", av_err2str(ret));
//        return ;
//    }
//    aframe->format = context->sample_fmt;
//    aframe->channels = context->channels;
//    aframe->channel_layout = context->channel_layout;
//    aframe->sample_rate = context->sample_rate;

//    frame_size = context->frame_size;
//    if (!frame_size)
//        frame_size = 1024;

//    frame_size_bytes = frame_size * (int)audio_size;

//    ret = av_samples_alloc(samples, NULL, context->channels,
//                           frame_size, context->sample_fmt, 0);
//    if (ret < 0) {
//        qWarning("Failed to create audio buffer: %s", av_err2str(ret));
//        return ;
//    }
}

/** Encoder input frame */
struct encoder_frame {
    /** Data for the frame/audio */
    uint8_t *data[MAX_AV_PLANES];

    /** size of each plane */
    uint32_t linesize[MAX_AV_PLANES];

    /** Number of frames (audio only) */
    uint32_t frames;

    /** Presentation timestamp */
    int64_t pts;
};
bool FFmpegAudioEncoder::encode()
{
//    encoder_frame * frame;
//    for (size_t i = 0; i < audio_planes; i++)
//        memcpy(samples[i], frame->data[i], frame_size_bytes);


//    AVRational time_base = {1, context->sample_rate};
//    AVPacket avpacket = {0};
//    int got_packet;
//    int ret;

//    aframe->nb_samples = frame_size;
//    aframe->pts = av_rescale_q(
//        total_samples, (AVRational){1, context->sample_rate},
//        context->time_base);

//    ret = avcodec_fill_audio_frame(
//        aframe, context->channels, context->sample_fmt,
//        samples[0], frame_size_bytes * context->channels,
//        1);
//    if (ret < 0) {
//        qWarning("avcodec_fill_audio_frame failed: %s", av_err2str(ret));
//        return false;
//    }

//    total_samples += frame_size;


//    ret = avcodec_send_frame(context, aframe);
//    if (ret == 0)
//        ret = avcodec_receive_packet(context, &avpacket);

//    got_packet = (ret == 0);

//    if (ret == AVERROR_EOF || ret == AVERROR(EAGAIN))
//        ret = 0;

//    if (ret < 0) {
//        qWarning("avcodec_encode_audio2 failed: %s", av_err2str(ret));
//        return false;
//    }
//    bool *received_packet;//TODO
//    *received_packet = !!got_packet;
//    if (!got_packet)
//        return true;

////    da_resize(packet_buffer, 0);
////    da_push_back_array(packet_buffer, avpacket.data, avpacket.size);

//    packet->pts = rescale_ts(avpacket.pts, context, time_base);
//    packet->dts = rescale_ts(avpacket.dts, context, time_base);
//    packet->data = packet_buffer.array;
//    packet->size = avpacket.size;
//    packet->type = OBS_ENCODER_AUDIO;
//    packet->timebase_num = 1;
//    packet->timebase_den = (int32_t)context->sample_rate;
//    av_free_packet(&avpacket);
    return true;
}
