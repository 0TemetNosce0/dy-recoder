#include "Muxer.h"

Muxer::Muxer()
{

}

void Muxer::exporttest()
{
//    //Convert PTS/DTS
//    pkt.pts = av_rescale_q_rnd(pkt.pts,
//                               in_stream->time_base,
//                               out_stream->time_base,
//                               (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
//    pkt.dts = av_rescale_q_rnd(pkt.dts,
//                               in_stream->time_base,
//                               out_stream->time_base,
//                               (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
//    pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
//    pkt.pos = -1;
//    pkt.stream_index = stream_index;

//    qDebug("Write 1 Packet. size:%5d\tpts:%lld\n", pkt.size, pkt.pts);
//    //Write
//    if (av_interleaved_write_frame(ofmt_ctx, &pkt) < 0) {
//        qDebug("Error muxing packet\n");
//        break;
//    }
//    av_free_packet(&pkt);
}


