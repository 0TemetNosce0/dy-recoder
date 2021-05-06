#include "AudioResampler.h"
#include <QDebug>
AudioResampler::AudioResampler()
{

}

AudioResampler::~AudioResampler()
{
    clearResampler();
}

void AudioResampler::resamplerCreate(int64_t out_ch_layout, AVSampleFormat out_sample_fmt, int out_sample_rate, int64_t in_ch_layout, AVSampleFormat in_sample_fmt, int in_sample_rate)
{

    context = swr_alloc_set_opts(nullptr,out_ch_layout,out_sample_fmt,out_sample_rate,in_ch_layout,in_sample_fmt,in_sample_rate, 0, nullptr);

    if (!context) {
        //        blog(LOG_ERROR, "swr_alloc_set_opts failed");
        abort();
        return ;
    }
    int errcode = swr_init(context);
    if (errcode != 0) {
        //        blog(LOG_ERROR, "avresample_open failed: error code %d",
        //             errcode);
        abort();
        return ;
    }
    inSampleRate = in_sample_rate;
    outputSampleRate = out_sample_rate;
    output_format = out_sample_fmt;
    output_ch = av_get_channel_layout_nb_channels(out_ch_layout);
}

void AudioResampler::clearResampler()
{
    if(context){
        swr_free(&context);
        context  = nullptr;
    }

}

bool AudioResampler::resample(uint8_t **output,
                              uint32_t *out_frames, uint64_t *ts_offset,
                              const uint8_t ** input, uint32_t in_frames)
{
    if (!context)
        return false;

    int ret;

        int64_t delay = swr_get_delay(context, inSampleRate);
        int estimated = (int)av_rescale_rnd(delay + (int64_t)in_frames,
                                             (int64_t)outputSampleRate,
                                             (int64_t)inSampleRate,
                                             AV_ROUND_UP);

        *ts_offset = (uint64_t)swr_get_delay(context, 1000000000);

        /* resize the buffer if bigger */
//        if (estimated > rs->output_size) {
//            if (rs->output_buffer[0])
//                av_freep(&rs->output_buffer[0]);

            av_samples_alloc(output, NULL, output_ch,
                             estimated, output_format, 0);

//            rs->output_size = estimated;
//        }

//    int out_count =0;//TODO
    ret = swr_convert(context, output, estimated/*out_count*/,
                      input, in_frames);

    if (ret < 0) {
        qDebug("swr_convert failed: %d", ret);
        abort();
        return false;
    }

    //    for (uint32_t i = 0; i < rs->output_planes; i++)
    //        output[i] = rs->output_buffer[i];

    *out_frames = (uint32_t)ret;
    return true;
}
