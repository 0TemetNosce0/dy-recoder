#include "EncodeAACTest.h"
#include <QDebug>
EncodeAACTest::EncodeAACTest()
{


    //    samples[0] = new [1024*4]int;
    //    samples[0] = new int[1024*4];
}


int EncodeAACTest::init_avformat()
{
    const char* out_file = "d:/tdjm.aac";          //Output URL
    //    int i;


    //    av_register_all();

    //Method 1.
    pFormatCtx = avformat_alloc_context();
    fmt = av_guess_format(NULL, out_file, NULL);
    pFormatCtx->oformat = fmt;


    //    //Method 2.
    //    //avformat_alloc_output_context2(&pFormatCtx, NULL, NULL, out_file);
    //    //fmt = pFormatCtx->oformat;

    //Open output URL
    if (avio_open(&pFormatCtx->pb,out_file, AVIO_FLAG_READ_WRITE) < 0){
        printf("Failed to open output file!\n");
        return -1;
    }

    audio_st = avformat_new_stream(pFormatCtx, 0);
    if (audio_st==NULL){
        return -1;
    }
    pCodec = avcodec_find_encoder(fmt->audio_codec);
    if (!pCodec){
        printf("Can not find encoder!\n");
        return -1;
    }

    return 0;
}

//新版版的ffmpeg 编码AAC只支持的AV_SAMPLE_FMT_FLTP，老版本的是AV_SAMPLE_FMT_S16，参数开之后avcodec_open2返回正确，但不要高兴太早；

//    2、很可能你传入的PCM数据是AV_SAMPLE_FMT_S16的，avcodec_encode_audio2还是返回-22错误，争取做法是需要AV_SAMPLE_FMT_S16的数据转为AV_SAMPLE_FMT_FLTP就可以了。下面贴一个ffmpeg4.0能编译通过执行编码的代码
//————————————————

int EncodeAACTest::init()
{
    enc_create();
    init_avformat();
    //Write Header
    avformat_write_header(pFormatCtx,NULL);
    //    void encode(uint8_t *data, size_t size);

    //    int got_frame=0;
    //    int ret=0;
    //    int size=0;

    //    int framenum=1000;                          //Audio frame number
    //    const char* out_file = "d:/tdjm.aac";          //Output URL
    //    int i;


    //    av_register_all();

    //    //Method 1.
    //    pFormatCtx = avformat_alloc_context();
    //    fmt = av_guess_format(NULL, out_file, NULL);
    //    pFormatCtx->oformat = fmt;


    //    //Method 2.
    //    //avformat_alloc_output_context2(&pFormatCtx, NULL, NULL, out_file);
    //    //fmt = pFormatCtx->oformat;

    //    //Open output URL
    //    if (avio_open(&pFormatCtx->pb,out_file, AVIO_FLAG_READ_WRITE) < 0){
    //        printf("Failed to open output file!\n");
    //        return -1;
    //    }

    //    audio_st = avformat_new_stream(pFormatCtx, 0);
    //    if (audio_st==NULL){
    //        return -1;
    //    }
    //    pCodec = avcodec_find_encoder(fmt->audio_codec);
    //    if (!pCodec){
    //        printf("Can not find encoder!\n");
    //        return -1;
    //    }

    //    //编码设置
    //    pCodecCtx = audio_st->codec;
    //    pCodecCtx->codec_id = fmt->audio_codec;
    //    pCodecCtx->codec_type = AVMEDIA_TYPE_AUDIO;
    //    pCodecCtx->sample_fmt = pCodec->sample_fmts[0];
    //    pCodecCtx->sample_rate= 44100;
    //    pCodecCtx->channel_layout=AV_CH_LAYOUT_STEREO;
    //    pCodecCtx->channels = av_get_channel_layout_nb_channels(pCodecCtx->channel_layout);
    //    pCodecCtx->bit_rate = 64000;
    //    pCodecCtx->profile=FF_PROFILE_AAC_MAIN ;
    //    pCodecCtx->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;
    //    //Show some information
    //    av_dump_format(pFormatCtx, 0, out_file, 1);



    //    //    swr = swr_alloc();
    //    //    av_opt_set_int(swr, "in_channel_layout",  AV_CH_LAYOUT_STEREO, 0);
    //    //    av_opt_set_int(swr, "out_channel_layout", AV_CH_LAYOUT_STEREO,  0);
    //    //    av_opt_set_int(swr, "in_sample_rate",     44100, 0);
    //    //    av_opt_set_int(swr, "out_sample_rate",    44100, 0);
    //    //    av_opt_set_sample_fmt(swr, "in_sample_fmt",  AV_SAMPLE_FMT_S16, 0);
    //    //    av_opt_set_sample_fmt(swr, "out_sample_fmt", AV_SAMPLE_FMT_FLTP,  0);
    //    //    swr_init(swr);
    //    //    uint8_t *outs[2];
    //    //    int len = 4096;

    //    //    outs[0]=(uint8_t *)malloc(len);//len 为4096
    //    //    outs[1]=(uint8_t *)malloc(len);


    //    if ((ret = avcodec_open2(pCodecCtx, pCodec,NULL)) < 0){
    //        printf("Failed to open encoder!\n");
    //        return -1;
    //    }
    //    pFrame = av_frame_alloc();
    //    pFrame->nb_samples= pCodecCtx->frame_size;
    //    pFrame->format=  pCodec->sample_fmts[0];

    //    size = av_samples_get_buffer_size(NULL, pCodecCtx->channels,pCodecCtx->frame_size,pCodecCtx->sample_fmt, 1);
    //    //    frame_buf = (uint8_t *)av_malloc(size);
    //    //    avcodec_fill_audio_frame(pFrame, pCodecCtx->channels, pCodecCtx->sample_fmt,(const uint8_t*)frame_buf, size, 1);

    //    //Write Header
    //    avformat_write_header(pFormatCtx,NULL);

    //    //    av_new_packet(&pkt,size);

    //    //    for (i=0; i<framenum; i++){
    //    //        //Read PCM
    //    ////        if (fread(frame_buf, 1, size, in_file) <= 0){
    //    ////            printf("Failed to read raw data! \n");
    //    ////            return -1;
    //    ////        }else if(feof(in_file)){
    //    ////            break;
    //    ////        }
    //    ////        int count=swr_convert(swr, outs,len*4,(const uint8_t **)&frame_buf,len/4);//len 为4096
    //    //        pFrame->data[0] =(uint8_t*)outs[0];//audioFrame 是VFrame
    //    //        pFrame->data[1] =(uint8_t*)outs[1];


    //    //        //pFrame->data[0] = frame_buf;  //PCM Data
    //    //        pFrame->pts=i*100;
    //    //        got_frame=0;
    //    //        //Encode
    //    //        ret = avcodec_encode_audio2(pCodecCtx, &pkt,pFrame, &got_frame);
    //    //        if(ret < 0){
    //    //            printf("Failed to encode!\n");
    //    //            return -1;
    //    //        }
    //    //        if (got_frame==1){
    //    //            printf("Succeed to encode 1 frame! \tsize:%5d\n",pkt.size);
    //    //            pkt.stream_index = audio_st->index;
    //    //            ret = av_write_frame(pFormatCtx, &pkt);
    //    //            av_free_packet(&pkt);
    //    //        }
    //    //    }

    return false;
}

bool EncodeAACTest::initialize_codec()
{
    int ret;

    aframe = av_frame_alloc();
    if (!aframe) {
        qDebug("Failed to allocate audio frame");
        return false;
    }

    ret = avcodec_open2(context, codec, NULL);
    if (ret < 0) {
        //        struct dstr error_message = {0};
        //        dstr_printf(&error_message, "Failed to open AAC codec: %s",
        //                    av_err2str(ret));
        //        obs_encoder_set_last_error(enc->encoder, error_message.array);
        //        dstr_free(&error_message);
//        qDebug("Failed to open AAC codec: %s", av_err2str(ret));
        return false;
    }
    aframe->format = context->sample_fmt;
    aframe->channels = context->channels;
    aframe->channel_layout = context->channel_layout;
    aframe->sample_rate = context->sample_rate;

    frame_size = context->frame_size;
    if (!frame_size)
        frame_size = 1024;

    frame_size_bytes = frame_size * (int)audio_size;

    ret = av_samples_alloc(samples, NULL, context->channels,
                           frame_size, context->sample_fmt, 0);
    if (ret < 0) {
//        qDebug("Failed to create audio buffer: %s", av_err2str(ret));
        return false;
    }

    return true;
}

void EncodeAACTest::encode(uint8_t * data,size_t size)
{

    int newSize = size+packet_buffer.size();
    if(packet_buffer.capacity()<newSize){

        packet_buffer.resize(newSize);
    }

    memcpy(packet_buffer.data()+packet_bufferSize+packet_bufferStartPos,data,size);

    packet_bufferSize += size;
    while(packet_bufferSize/2/4>1024){//编码


        {//转为plane

            float * dataF = (float* )data;
            float * samplesP=  (float* )samples[0];
            for(int i =0 ;i<1024;i++){


                *samplesP = *dataF;
                dataF = dataF+2;
                samplesP++;
            }


        }

        //        av_new_packet(&pkt,size);

        //        pFrame->data[0] = frame_buf;  //PCM Data
        //        pFrame->pts=i*100;
        //        got_frame=0;
        //        //Encode
        //        ret = avcodec_encode_audio2(pCodecCtx, &pkt,pFrame, &got_frame);
        //        if(ret < 0){
        //            printf("Failed to encode!\n");
        //            return -1;
        //        }
        //        if (got_frame==1){
        //            printf("Succeed to encode 1 frame! \tsize:%5d\n",pkt.size);
        //            pkt.stream_index = audio_st->index;
        //            ret = av_write_frame(pFormatCtx, &pkt);
        //            av_free_packet(&pkt);
        //        }
        AVRational time_base = {1, context->sample_rate};
        AVPacket avpacket = {0};
        int got_packet;
        int ret;
        aframe->nb_samples = frame_size;
        aframe->pts = av_rescale_q(
            total_samples, time_base/*(AVRational){1, context->sample_rate}*/,
            context->time_base);

        ret = avcodec_fill_audio_frame(
            aframe, context->channels, context->sample_fmt,
            samples[0], frame_size_bytes * context->channels,
            1);
        if (ret < 0) {
//            qDebug("avcodec_fill_audio_frame failed: %s", av_err2str(ret));
            return ;
        }

        total_samples += frame_size;

        ret = avcodec_encode_audio2(context, &avpacket, aframe,
                                    &got_packet);

        if (ret < 0) {
//            qDebug("avcodec_encode_audio2 failed: %s", av_err2str(ret));
            return ;
        }


        //        *received_packet = !!got_packet;
        //        if (!got_packet)
        //            return ;

        //        da_resize(enc->packet_buffer, 0);
        //        da_push_back_array(enc->packet_buffer, avpacket.data, avpacket.size);

        //        packet->pts = rescale_ts(avpacket.pts, enc->context, time_base);
        //        packet->dts = rescale_ts(avpacket.dts, enc->context, time_base);
        //        packet->data = enc->packet_buffer.array;
        //        packet->size = avpacket.size;
        //        packet->type = OBS_ENCODER_AUDIO;
        //        packet->timebase_num = 1;
        //        packet->timebase_den = (int32_t)enc->context->sample_rate;
        //        av_free_packet(&avpacket);

        {//write
            if (got_packet==1){
                qDebug("Succeed to encode 1 frame! \tsize:%5d\n",avpacket.size);
                avpacket.stream_index = audio_st->index;
                ret = av_write_frame(pFormatCtx, &avpacket);
                av_free_packet(&avpacket);
            }

        }


        packet_bufferStartPos -=1024*2*4;
        packet_bufferSize-=1024*2*4;
    }




    memmove(packet_buffer.data(),packet_buffer.data()+packet_bufferStartPos,packet_bufferSize);

    packet_bufferStartPos =0;

}

bool EncodeAACTest::enc_create()
{

    av_register_all();
    codec = avcodec_find_encoder_by_name("aac");


    if (!codec) {
        qDebug("Couldn't find encoder");
        goto fail;
    }

    int bitrate = 160;
    if (!bitrate) {
        qDebug("Invalid bitrate specified");
        return false;
    }

    context = avcodec_alloc_context3(codec);
    if (!context) {
        qDebug("Failed to create codec context");
        goto fail;
    }

    context->bit_rate = bitrate * 1000;
    const struct audio_output_info *aoi;


    //    //编码设置
    //    pCodecCtx = audio_st->codec;
    //    pCodecCtx->codec_id = fmt->audio_codec;
    //    pCodecCtx->codec_type = AVMEDIA_TYPE_AUDIO;
    //    pCodecCtx->sample_fmt = pCodec->sample_fmts[0];
    //    pCodecCtx->sample_rate= 44100;
    //    pCodecCtx->channel_layout=AV_CH_LAYOUT_STEREO;
    //    pCodecCtx->channels = av_get_channel_layout_nb_channels(pCodecCtx->channel_layout);
    //    pCodecCtx->bit_rate = 64000;
    //    pCodecCtx->profile=FF_PROFILE_AAC_MAIN ;
    //    pCodecCtx->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;
    context->channel_layout = AV_CH_LAYOUT_STEREO;
    context->channels = av_get_channel_layout_nb_channels(context->channel_layout);
    context->sample_rate = 44100;
    context->sample_fmt =/*codec->sample_fmts
                              ? codec->sample_fmts[0]
                              :*/ AV_SAMPLE_FMT_FLTP;
    /* check to make sure sample rate is supported */
    if (codec->supported_samplerates) {
        const int *rate = codec->supported_samplerates;
        int cur_rate = context->sample_rate;
        int closest = 0;

        while (*rate) {
            int dist = abs(cur_rate - *rate);
            int closest_dist = abs(cur_rate - closest);

            if (dist < closest_dist)
                closest = *rate;
            rate++;
        }

        if (closest)
            context->sample_rate = closest;
    }

    if (strcmp(codec->name, "aac") == 0) {
        av_opt_set(context->priv_data, "aac_coder", "fast", 0);
    }

    qDebug("bitrate: %" PRId64 ", channels: %d, channel_layout: %x\n",
           (int64_t)context->bit_rate / 1000,
           (int)context->channels,
           (unsigned int)context->channel_layout);

    //    init_sizes(enc, audio);

    /* enable experimental FFmpeg encoder if the only one available */
    context->strict_std_compliance = -2;

    context->flags = AV_CODEC_FLAG_GLOBAL_HEADER;

    if (!initialize_codec()){
        qDebug("initialize_codec fail");
    }




    {

        //    //Method 1.
        //            pFormatCtx = avformat_alloc_context();
        //            fmt = av_guess_format(NULL, out_file, NULL);
        //            pFormatCtx->oformat = fmt;


        //    //Method 2.
        //    //avformat_alloc_output_context2(&pFormatCtx, NULL, NULL, out_file);
        //    //fmt = pFormatCtx->oformat;

        //    //Open output URL
        //    if (avio_open(&pFormatCtx->pb,out_file, AVIO_FLAG_READ_WRITE) < 0){
        //        printf("Failed to open output file!\n");
        //        return -1;
        //    }

        //    audio_st = avformat_new_stream(pFormatCtx, 0);
        //    if (audio_st==NULL){
        //        return -1;
        //    }
        //    pCodec = avcodec_find_encoder(fmt->audio_codec);
        //    if (!pCodec){
        //        printf("Can not find encoder!\n");
        //        return -1;
        //    }
    }

fail:
    //    enc_destroy(enc);
    return true;
}

void EncodeAACTest::end()
{
    //    //Flush Encoder
    //    ret = flush_encoder(pFormatCtx,0);
    //    if (ret < 0) {
    //        printf("Flushing encoder failed\n");
    //        return -1;
    //    }

    //Write Trailer
    av_write_trailer(pFormatCtx);

    //    //Clean
    //    if (audio_st){
    //        avcodec_close(audio_st->codec);
    //        av_free(pFrame);
    //        av_free(frame_buf);
    //    }
    avio_close(pFormatCtx->pb);
    avformat_free_context(pFormatCtx);
}
