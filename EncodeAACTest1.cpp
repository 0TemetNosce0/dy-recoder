#include "EncodeAACTest1.h"
#include <QDebug>
EncodeAACTest1::EncodeAACTest1() {}
static void log_callback(void *ptr, int level, const char *fmt, va_list vl) {
    switch (level) {
    case AV_LOG_QUIET:
    case AV_LOG_PANIC:
    case AV_LOG_FATAL:
    case AV_LOG_ERROR:
        //        LOG_ERROR2(fmt, vl);
        //        break;
        qDebug(fmt, vl);
    case AV_LOG_WARNING:
        //        LOG_WARNING2(fmt, vl);
        qDebug(fmt, vl);
        break;
    case AV_LOG_INFO:
    case AV_LOG_VERBOSE:
        //        LOG_INFO2(fmt, vl);

        qDebug(fmt, vl);
        break;
    case AV_LOG_DEBUG:
    case AV_LOG_TRACE:
        //LOG_DEBUG2(fmt, vl);
        qDebug(fmt, vl);
        break;
    default:
        break;
    }
}
int EncodeAACTest1::init() {
    av_register_all();
    //    //log 回调
    av_log_set_level(AV_LOG_INFO);
    av_log_set_callback(log_callback);
    char saveFile[30] = "d:/tdjm.aac";
    //Method 1.
    //        format_context = avformat_alloc_context();
    //        format = av_guess_format(NULL, saveFile, NULL);
    //        format_context->oformat = format;

    //Method 2.
    avformat_alloc_output_context2(&format_context, NULL, NULL, saveFile);
    format = format_context->oformat;

    //Open output URL
    if (avio_open(&format_context->pb, saveFile, AVIO_FLAG_READ_WRITE) < 0) {
        printf("Failed to open output file!\n");
        return -1;
    }

    audio_stream = avformat_new_stream(format_context, 0);
    if (audio_stream == NULL) {
        return -1;
    }
    encode_codec = avcodec_find_encoder(format->audio_codec);
    if (!encode_codec) {
        printf("Can not find encoder!\n");
        return -1;
    }

    encode_context = avcodec_alloc_context3(encode_codec);
    if (!encode_context) {
        qDebug("Failed to create codec context");
        //        goto fail;
    }

    //    encode_context->bit_rate = 64000/*bitrate * 1000*/;
//    encode_context = audio_stream->codec;                                //流的code
    encode_context->codec_id = encode_codec->id /*format->audio_codec*/; // enc->codec_id = codec->id;

    encode_context->codec_type = AVMEDIA_TYPE_AUDIO;
    encode_context->sample_fmt = AV_SAMPLE_FMT_FLTP /*pCodec->sample_fmts[0]*/;
    encode_context->sample_rate = 44100;
    encode_context->channel_layout = AV_CH_LAYOUT_STEREO;
    encode_context->channels = av_get_channel_layout_nb_channels(encode_context->channel_layout);
    encode_context->bit_rate = 64000;
    encode_context->profile = FF_PROFILE_AAC_MAIN;
    encode_context->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;
    /* check to make sure sample rate is supported */
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

    if (strcmp(encode_codec->name, "aac") == 0) {
        av_opt_set(encode_context->priv_data, "aac_coder", "fast", 0);
    }

    qDebug("bitrate: %" PRId64 ", channels: %d, channel_layout: %x\n",
           (int64_t) encode_context->bit_rate / 1000,
           (int) encode_context->channels,
           (unsigned int) encode_context->channel_layout);

    //    init_sizes(enc, audio);

    /* enable experimental FFmpeg encoder if the only one available */
    encode_context->strict_std_compliance = -2;

    encode_context->flags = AV_CODEC_FLAG_GLOBAL_HEADER;

    int ret;

    aframe = av_frame_alloc();
    if (!aframe) {
        qDebug("Failed to allocate audio frame");
        return false;
    }

    ret = avcodec_open2(encode_context, encode_codec, NULL);
    if (ret < 0) {
        //        struct dstr error_message = {0};
        //        dstr_printf(&error_message, "Failed to open AAC codec: %s",
        //                    av_err2str(ret));
        //        obs_encoder_set_last_error(enc->encoder, error_message.array);
        //        dstr_free(&error_message);
        //        qDebug("Failed to open AAC codec: %s", av_err2str(ret));
        return false;
    }
    aframe->format = encode_context->sample_fmt;
    aframe->channels = encode_context->channels;
    aframe->channel_layout = encode_context->channel_layout;
    aframe->sample_rate = encode_context->sample_rate;

    frame_size = encode_context->frame_size;
    if (!frame_size)
        frame_size = 1024;

    frame_size_bytes = frame_size * (int) audio_size;

    ret = av_samples_alloc(samples,
                           NULL,
                           encode_context->channels,
                           frame_size,
                           encode_context->sample_fmt,
                           0);
    if (ret < 0) {
        //        qDebug("Failed to create audio buffer: %s", av_err2str(ret));
        return false;
    }

        ret = avcodec_parameters_from_context(audio_stream->codecpar, encode_context);
        if (ret < 0) {
            qDebug("Failed avcodec_parameters_from_context");
            //        av_strerror(ret, err, AV_ERROR_MAX_STRING_SIZE);
            //        throw std::runtime_error(err);
        }
    //Write Header
    avformat_write_header(format_context, NULL);
    return true;
}

void EncodeAACTest1::end() {
    //    //    //Flush Encoder
    //    //    ret = flush_encoder(pFormatCtx,0);
    //    //    if (ret < 0) {
    //    //        printf("Flushing encoder failed\n");
    //    //        return -1;
    //    //    }

    //Write Trailer
    av_write_trailer(format_context);

    //    //Clean
    //    if (audio_st){
    //        avcodec_close(audio_st->codec);
    //        av_free(pFrame);
    //        av_free(frame_buf);
    //    }
    avio_close(format_context->pb);
    avformat_free_context(format_context);

//    {
//        auto s = samples[1];
//        for(int i=0;i<1024*2*4;i++){

//            *s=0;
//            s++;
//        }
//    }
}

void EncodeAACTest1::encode(uint8_t *data, size_t size) {
    int newSize = size + packet_buffer.size();
    if (packet_buffer.capacity() < newSize) {
        packet_buffer.resize(newSize);
    }

    memcpy(packet_buffer.data() + packet_bufferSize + packet_bufferStartPos, data, size);

    packet_bufferSize += size;
    while (packet_bufferSize / 2 / 4 > 1024) { //编码

        { //转为plane

            float *dataF = (float *) packet_buffer.data();
            float *samplesP = (float *) samples[0];
                        for (int i = 0; i < 1024; i++) {

                            *samplesP = *dataF;
                            if (std::isinf(*samplesP) || std::isnan(*samplesP)) {
                                *samplesP = 0;

                            }else{
//                                qDebug()<<11111111111<<*samplesP;
                            }
                            dataF = dataF + 2;
                            samplesP++;
                        }
        }

        AVRational time_base = {1, encode_context->sample_rate};
        AVPacket avpacket = {0};
        int got_packet;
        int ret;
        aframe->nb_samples = frame_size;
        aframe->pts = av_rescale_q(total_samples,
                                   time_base /*(AVRational){1, context->sample_rate}*/,
                                   encode_context->time_base);

        ret = avcodec_fill_audio_frame(aframe,
                                       encode_context->channels,
                                       encode_context->sample_fmt,
                                       samples[0],
                                       frame_size_bytes * encode_context->channels,
                                       1);
        if (ret < 0) {
            //            qDebug("avcodec_fill_audio_frame failed: %s", av_err2str(ret));
            return;
        }

        total_samples += frame_size;

        ret = avcodec_encode_audio2(encode_context, &avpacket, aframe, &got_packet);

        if (ret < 0) {
            //            qDebug("avcodec_encode_audio2 failed: %s", av_err2str(ret));
            return;
        }

        { //write
            if (got_packet == 1) {
                static int test  =0;
                qDebug("Succeed to encode 1 frame! \tsize:%5d\n", test/*avpacket.size*/);
                test++;
                avpacket.stream_index = audio_stream->index;
                ret = av_write_frame(format_context, &avpacket);
                av_free_packet(&avpacket);
            }
        }

        packet_bufferStartPos += 1024 * 2 * 4;
        packet_bufferSize -= 1024 * 2 * 4;
    }

    memmove(packet_buffer.data(), packet_buffer.data() + packet_bufferStartPos, packet_bufferSize);

    if(packet_buffer.size()<(packet_bufferStartPos+packet_bufferSize)){
        qDebug()<<"ddddddddddd"<<packet_buffer.size();
    }

    packet_bufferStartPos = 0;
}
