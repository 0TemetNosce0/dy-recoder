[TOC]

# 网址

https://trac.ffmpeg.org/wiki

ffmpeg文档 https://ffmpeg.org/documentation.html

ffmpeg download https://ffmpeg.org/download.html

ffmpeg  filters http://ffmpeg.org/ffmpeg-filters.html

ffmpeg   Error Codes https://ffmpeg.org/doxygen/trunk/group__lavu__error.html

ffmpeg doxygen  https://ffmpeg.org/doxygen/trunk/index.html

ffmpeg 的 Mux 主要分为 三步操作：

    avformat_write_header ： 写文件头
    
    av_write_frame/av_interleaved_write_frame： 写packet
    
    av_write_trailer ： 写文件尾
————————————————
版权声明：本文为CSDN博主「一步-refresh」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/yibu_refresh/article/details/52884413

# [雷霄骅](https://blog.csdn.net/leixiaohua1020)

https://blog.csdn.net/leixiaohua1020/article/details/44199673

# 基本知识

**编解码**

　　编解码器（codec）指的是一个能够对一个信号或者一个数据流进行变换的设备或者程序。这里指的变换既包括将  信号或者数据流进行编码（通常是为了传输、存储或者加密）或者提取得到一个编码流的操作，也包括为了观察或者处理从这个编码流中恢复适合观察或操作的形式的操作。编解码器经常用在视频会议和流媒体等应用中。

**容器** 

　　很多多媒体数据流需要同时包含音频数据和视频数据，这时通常会加入一些用于音频和视频数据同步的元数据，例如字幕。这三种数据流可能会被不同的程序，进程或者硬件处理，但是当它们传输或者存储的时候，这三种数据通常是被封装在一起的。通常这种封装是通过视频文件格 式来实现的，例如常见的*.mpg, *.avi, *.mov, *.mp4, *.rm, *.ogg or *.tta.  这些格式中有些只能使用某些编解码器，而更多可以以容器的方式使用各种编解码器。

**分辨率** 

　　分辨率，泛指量测或显示系统对细节的分辨能力。此概念可以用时间、空间等领域的量测。日常用语中之分辨率多用于图像的清晰度。分辨率越高代表图像品质越好，越能表现出更多的细节。但相对的，因为纪录的信息越多，文件也就会越大。目前个人电脑里的图像，可以使用图像 处理软件，调整图像的大小、编修照片等。例如 photoshop，或是photoimpact等软件。

　**图像分辨率** ：

　　用以描述图像细节分辨能力，同样适用于数字图像、胶卷图像、及其他类型图像。常用'线每毫米'、  '线每英吋'等来衡量。通常，“分辨率”被表示成每一个方向上的像素数量，比如640x480等。而在某些情况下，它也可以同时表示成“每英吋像素”  （pixels per inch，ppi）以及图形的长度和宽度。比如72ppi，和8x6英吋。

　**视频分辨率** ：

各种电视规格分辨率比较视  频的画面大小称为“分辨率”。数位视频以像素为度量单位，而类比视频以水平扫瞄线数量为度量单位。标清电视频号分辨率为  720/704/640x480i60（NTSC）或768/720x576i50（PAL/SECAM）。新的高清电视（HDTV）分辨率可达  1920x1080p60，即每条水平扫瞄线有1920个像素，每个画面有1080条扫瞄线，以每秒钟60张画面的速度播放。

**画面更新率fps**

　　Frame  rate中文常译为“画面更新率”或“帧率”，是指视频格式每秒钟播放的静态画面数量。典型的画面更新率由早期的每秒6或8张（frame  persecond，简称fps），至现今的每秒120张不等。PAL (欧洲，亚洲，澳洲等地的电视广播格式) 与 SECAM  (法国，俄国，部分非洲等地的电视广播格式) 规定其更新率为25fps，而NTSC (美国，加拿大，日本等地的电视广播格式)  则规定其更新率为29.97  fps。电影胶卷则是以稍慢的24fps在拍摄，这使得各国电视广播在播映电影时需要一些复杂的转换手续（参考Telecine转换）。要达成最基本的视觉暂留效果大约需要10fps的速度。

**压缩方法**

**有损压缩和无损压缩**

　　在视频压缩中有损（Lossy  ）和无损（Lossless）的概念与静态图像中基本类似。无损压缩也即压缩前和解压缩后的数据完全一致。多数的无损压缩都采用RLE行程编码算法。有损  压缩意味着解压缩后的数据与压缩前的数据不一致。在压缩的过程中要丢失一些人眼和人耳所不敏感的图像或音频信息，而且丢失的信息不可恢复。几乎所有高压缩的算法都采用有损压缩，这样才能达到低数据率的目标。丢失的数据率与压缩比有关，压缩比越小，丢失的数据越多，解压缩后的效果一般越差。此外，某些有损压 缩算法采用多次重复压缩的方式，这样还会引起额外的数据丢失。

- 无损格式，例如WAV，PCM，TTA，FLAC，AU，APE，TAK，WavPack(WV)
- 有损格式，例如MP3，Windows Media Audio（WMA），Ogg Vorbis（OGG），AAC

**帧内压缩和帧间压缩**

　　帧内（Intraframe）压缩也称为空间压缩 （Spatial  compression）。当压缩一帧图像时，仅考虑本帧的数据而不考虑相邻帧之间的冗余信息，这实际上与静态图像压缩类似。帧内一般采用有损压缩算法，由于帧内压缩时各个帧之间没有相互关系，所以压缩后的视频数据仍可以以帧为单位进行编辑。帧内压缩一般达不到很高的压缩。

　　采用帧间（Interframe）压缩是基于许多视频或  动画的连续前后两帧具有很大的相关性，或者说前后两帧信息变化很小的特点。也即连续的视频其相邻帧之间具有冗余信息，根据这一特性，压缩相邻帧之间的冗余量就可以进一步提高压缩量，减小压缩比。帧间压缩也称为时间压缩（Temporalcompression），它通过比较时间轴上不同帧之间的数据进行压缩。帧间压缩一般是无损的。帧差值（Frame differencing）算法是一种典型的时间压缩法，它通过比较本帧与相邻帧之间的差异，仅记录本帧与其相邻帧的差值，这样可以大大减少数据量。

**对称编码和不对称编码** 

　　对称性（symmetric）是压缩编码的一个关键特  征。对称意味着压缩和解压缩占用相同的计算处理能力和时间，对称算法适合于实时压缩和传送视频，如视频会议应用就以采用对称的压缩编码算法为好。而在电子出版和其它多媒体应用中，一般是把视频预先压缩处理好，尔后再播放，因此可以采用不对称（asymmetric）编码。不对称或非对称意味着压缩时需要花费大量的处理能力和时间，而解压缩时则能较好地实时回放，也即以不同的速度进行压缩和解压缩。一般地说，压缩一段视频的时间比回放（解压缩）该视频的时间 要多得多。例如，压缩一段三分钟的视频片断可能需要10多分钟的时间，而该片断实时回放时间只有三分钟。



资料（港台将information翻译为资料）压缩是透过去除资料中的冗余资讯而达成。就视讯资料而言，资料中的冗余资讯可以分成四类：

时间上的冗余资讯（temporal redundancy）
　　在视讯资料中，相邻的帧（frame）与帧之间通常有很强的关连性，这样的关连性即为时间上的冗余资讯。这即是上一次学习中的帧间压缩。 

空间上的冗余资讯（spatial redundancy）
　　在同一张帧之中，相邻的像素之 间通常有很强的关连性，这样的关连性即为空间上的冗余资讯。这即是上一次学习中的帧内压缩。 

统计上的冗余资讯（statistical redundancy）
　　统计上的冗余资讯指的是欲编码的符号（symbol）的机率分布是不均匀（non-uniform）的。 

感知上的冗余资讯（perceptual redundancy）
　　感知上的冗余资讯是指在人在观看视讯时，人眼无法察觉的资讯。 

 

　　视讯压缩（英文：Video  compression）是指运用资料压缩技术将数位视讯资料中的冗余资讯去除，降低表示原始视讯所需的资料量，以便视讯资料的传输与储存。实际上，原始视讯资料的资料量往往过大，例如未经压缩的电视品质视讯资料的位元率高达216Mbps，绝大多数的应用无法处理如此庞大的资料量，因此视讯压缩是必要的。目前最新的视讯编码标准为ITU-T视讯编码专家组（VCEG）和ISO／IEC动态图像专家组（MPEG）联合组成的联合视讯组（JVT，Joint Video Team）所提出的H.264/AVC。

　　一个典型的视讯编码器：在进行当前信号编码时，编码器首先会产生对当前信号做预测的信号，称作预测信号（predicted signal），预测的方式可以是时间上的预测（interprediction），亦即使用先前帧的信号做预测，或是空间上的预测 （intra  prediction），亦即使用同一张帧之中相邻像素的信号做预测。得到预测信号后，编码器会将当前信号与预测信号相减得到残余信号（residual  signal），并只对残余信号进行编码，如此一来，可以去除一部份时间上或是空间上的冗余资讯。接着，编码器并不会直接对残余信号进行编码，而是先将残余信号经过变换（通常为离散余弦变换）然后量化以 进一步去除空间上和感知上的冗余资讯。量化后得到的量化系数会再透过熵编码，去除统计上的冗余资讯。 

| **视讯编码标准发展** |                                                              |                                                              |                                |                                                              |
| -------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------ | ------------------------------------------------------------ |
| **年份**             | **标准**                                                     | **制定组织**                                                 | **解除版权保护 （DRM-free ）** | **主要应用**                                                 |
| **1984**             | [H.120](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DH.120%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) | [ITU-T](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FITU-T) | 是                             |                                                              |
| **1990**             | [H.261](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FH.261) | [ITU-T](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FITU-T) | 是                             | [视讯会议](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2F%E8%A6%96%E8%A8%8A%E6%9C%83%E8%AD%B0)、[视讯通话](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3D%E8%A6%96%E8%A8%8A%E9%80%9A%E8%A9%B1%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) |
| **1993**             | [MPEG-1 第二部份](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DMPEG-1_%E7%AC%AC%E4%BA%8C%E9%83%A8%E4%BB%BD%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) | [ISO](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FISO) ／[IEC](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FIEC) | 是                             | 影音光碟（[VCD](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FVCD) ） |
| **1995**             | [H.262/MPEG-2 第二部份](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DH.262%2FMPEG-2_%E7%AC%AC%E4%BA%8C%E9%83%A8%E4%BB%BD%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) | [ISO ](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FISO)／ [IEC ](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FIEC)、[ITU-T](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FITU-T) | 否                             | [DVD影碟](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DDVD%E5%BD%B1%E7%A2%9F%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1)（[DVD-Video](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FDVD-Video) ）、[蓝光](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2F%E8%97%8D%E5%85%89)（[Blu-Ray](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DBlu-Ray%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) ）影碟、数位视讯广播（[DVB](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FDVB) ）、[SVCD](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FSVCD) |
| **1996**             | [H.263](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FH.263) [[6\]](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2F%E8%A7%86%E9%A2%91%E5%8E%8B%E7%BC%A9%23_note-H263-5) | [ITU-T](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FITU-T) |                                | [视讯会议](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2F%E8%A6%96%E8%A8%8A%E6%9C%83%E8%AD%B0)、[视讯通话](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3D%E8%A6%96%E8%A8%8A%E9%80%9A%E8%A9%B1%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1)、[3G](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2F3G) 手机视讯（[3GP](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2F3GP) ） |
| **1999**             | [MPEG-4 第二部份](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DMPEG-4_%E7%AC%AC%E4%BA%8C%E9%83%A8%E4%BB%BD%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) | [ISO](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FISO) ／[IEC](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FIEC) | 否                             |                                                              |
| **2003**             | [H.264/MPEG-4 AVC](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FH.264%2FMPEG-4_AVC) [[1\]](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2F%E8%A7%86%E9%A2%91%E5%8E%8B%E7%BC%A9%23_note-H264_AVC-0) | [ISO ](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FISO)／ [IEC ](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FIEC)、[ITU-T](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FITU-T) | 否                             | [蓝光](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2F%E8%97%8D%E5%85%89)（[Blu-Ray](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DBlu-Ray%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) ）影碟、数位视讯广播（[DVB](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FDVB) ）、[iPod](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FIPod) 视讯、[高画质DVD](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3D%E9%AB%98%E7%95%AB%E8%B3%AADVD%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1)（[HD DVD](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FHD_DVD) ） |

常见的编解码见下表，在以后会分类论述： 

| 视频codec                                                    | [ISO](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2F%E5%9C%8B%E9%9A%9B%E6%A8%99%E6%BA%96%E5%8C%96%E7%B5%84%E7%B9%94) /[IEC](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2F%E5%9B%BD%E9%99%85%E7%94%B5%E5%B7%A5%E5%A7%94%E5%91%98%E4%BC%9A) | [MJPEG](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FMotion_JPEG) **·** [Motion JPEG 2000](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FJPEG_2000%23Motion_JPEG_2000) **·** [MPEG-1](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FMPEG-1) **·** [MPEG-2](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FMPEG-2) ([Part 2](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DH.262%2FMPEG-2_Part_2%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) )**·** [MPEG-4](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FMPEG-4) ([Part 2/ASP](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DMPEG-4_Part_2%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [Part 10/AVC](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FH.264%2FMPEG-4_AVC) )**·** [HVC](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DHigh-performance_Video_Coding%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| [ITU-T](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2F%E5%9B%BD%E9%99%85%E7%94%B5%E4%BF%A1%E8%81%94%E7%9B%9F%E8%BF%9C%E7%A8%8B%E9%80%9A%E4%BF%A1%E6%A0%87%E5%87%86%E5%8C%96%E7%BB%84) | [H.120](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DH.120%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [H.261](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FH.261) **·** [H.262](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DH.262%2FMPEG-2_Part_2%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [H.263](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FH.263) **·** [H.264](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FH.264%2FMPEG-4_AVC) **·** [H.265](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FH.265) |                                                              |
| 其它                                                         | [AMV](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FAMV_video_format) **·** [AVS](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FAudio_Video_Standard) **·** [Bink](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FBink_Video) **·** [CineForm](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FCineForm) **·** [Cinepak](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FCinepak) **·** [Dirac](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FDirac_%28codec%29) **·** [DV](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FDV) **·** [Indeo](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FIndeo) **·** [Microsoft Video 1](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMicrosoft_Video_1) **·** [OMS Video](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FOMS_Video) **·** [Pixlet](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FPixlet) **·** [RealVideo](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FRealVideo) **·** [RTVideo](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FRTVideo) **·** [SheerVideo](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FSheerVideo) **·** [Smacker](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FSmacker_video) **·** [Sorenson Video & Sorenson Spark ](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FSorenson_codec)**·** [Theora ](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FTheora)**·** [VC-1 ](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FVC-1)**·** [VP3 ](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FVP3)**·** [VP6 ](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FVP6)**·** [VP7 ](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FVP7)**·** [VP8 ](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FVP8)**·** [WMV ](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FWindows_Media_Video) |                                                              |
| 音频 codec                                                   | [ISO](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2F%E5%9C%8B%E9%9A%9B%E6%A8%99%E6%BA%96%E5%8C%96%E7%B5%84%E7%B9%94) /[IEC](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2F%E5%9B%BD%E9%99%85%E7%94%B5%E5%B7%A5%E5%A7%94%E5%91%98%E4%BC%9A) [MPEG](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FMPEG) | [MPEG-1 Layer III (MP3)](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FMP3) **·** [MPEG-1 Layer II](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FMPEG-1_Audio_Layer_II) **·** [MPEG-1 Layer I](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DMPEG-1_Audio_Layer_I%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [AAC](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FAdvanced_Audio_Coding) **·** [HE-AAC](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DHigh-Efficiency_Advanced_Audio_Coding%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [MPEG-4 ALS](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DAudio_Lossless_Coding%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [MPEG-4 SLS](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DMPEG-4_SLS%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [MPEG-4 DST](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FDirect_Stream_Transfer%23DST) |
| [ITU-T](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2F%E5%9B%BD%E9%99%85%E7%94%B5%E4%BF%A1%E8%81%94%E7%9B%9F%E8%BF%9C%E7%A8%8B%E9%80%9A%E4%BF%A1%E6%A0%87%E5%87%86%E5%8C%96%E7%BB%84) | [G.711](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FG.711) **·** [G.718](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DG.718%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [G.719](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DG.719%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [G.722](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FG.722) **·** [G.722.1](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DG.722.1%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [G.722.2](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DG.722.2%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [G.723](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FG.723) **·** [G.723.1](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DG.723.1%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [G.726](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FG.726) **·** [G.728](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DG.728%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [G.729](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FG.729) **·** [G.729.1](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DG.729.1%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) |                                                              |
| 其它                                                         | [AC-3](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FDolby_Digital) **·** [AMR](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FAdaptive_Multi-Rate_audio_codec) **·** [AMR-WB](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FAdaptive_Multi-Rate_Wideband) **·** [AMR-WB+](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FExtended_Adaptive_Multi-Rate_-_Wideband) **·** [Apple Lossless](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FApple_Lossless) **·** [ATRAC](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FAdaptive_Transform_Acoustic_Coding) **·** [DRA](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FDynamic_Resolution_Adaptation) **·** [DTS](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FDTS_%28sound_system%29) **·** [FLAC](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FFree_Lossless_Audio_Codec) **·** [GSM-HR](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FHalf_Rate) **·** [GSM-FR](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FFull_Rate) **·** [GSM-EFR](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FEnhanced_Full_Rate) **·** [iLBC](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FInternet_Low_Bit_Rate_Codec) **·** [Monkey's Audio](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMonkey%27s_Audio) **·** [TTA](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FTTA_%28codec%29) (True Audio)**·** [MT9](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMT9) **·** [μ-law](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2F%CE%9C-law_algorithm) **·** [Musepack](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMusepack) **·** [Nellymoser](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FNellymoser_Asao_Codec) **·** [OptimFROG](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FOptimFROG) **·** [OSQ](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FOriginal_Sound_Quality) **·** [RealAudio](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FRealAudio) **·** [RTAudio](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FRTAudio) **·** [SD2](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FDigidesign%23Sound_Designer_File_Formats) **·** [SHN](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FShorten) **·** [SILK](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FSILK) **·** [Siren](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FSiren_Codec) **·** [Speex](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FSpeex) **·** [TwinVQ](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FTwinVQ) **·** [Vorbis](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FVorbis) **·** [WavPack](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FWavPack) **·** [WMA](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FWindows_Media_Audio) |                                                              |
| 图像压缩                                                     | [ISO](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2F%E5%9C%8B%E9%9A%9B%E6%A8%99%E6%BA%96%E5%8C%96%E7%B5%84%E7%B9%94) /[IEC](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2F%E5%9B%BD%E9%99%85%E7%94%B5%E5%B7%A5%E5%A7%94%E5%91%98%E4%BC%9A) /[ITU-T](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2F%E5%9B%BD%E9%99%85%E7%94%B5%E4%BF%A1%E8%81%94%E7%9B%9F%E8%BF%9C%E7%A8%8B%E9%80%9A%E4%BF%A1%E6%A0%87%E5%87%86%E5%8C%96%E7%BB%84) | [JPEG](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FJPEG) **·** [JPEG 2000](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FJPEG_2000) **·** [JPEG XR](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DJPEG_XR%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [lossless JPEG](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DLossless_JPEG%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [JBIG](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FJBIG) **·** [JBIG2](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DJBIG2%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [PNG](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FPortable_Network_Graphics) **·** [WBMP](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DWireless_Application_Protocol_Bitmap_Format%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) |
| Others                                                       | [APNG](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FAPNG) **·** [BMP](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FBMP) **·** [DjVu](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FDjVu) **·** [EXR](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DOpenEXR%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [GIF](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FGraphics_Interchange_Format) **·** [ICER](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DICER%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [ILBM](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DILBM%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [MNG](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FMultiple-image_Network_Graphics) **·** [PCX](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FPCX) **·** [PGF](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DProgressive_Graphics_File%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [TGA](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DTruevision_TGA%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [TIFF](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FTagged_Image_File_Format) |                                                              |
| 媒体容器                                                     | 通用                                                         | [3GP](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2F3GP) **·** [ASF](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DAdvanced_Systems_Format%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [AVI](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FAudio_Video_Interleave) **·** [Bink](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DBink_Video%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [BXF](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DBroadcast_eXchange_Format%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [DMF](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FDivX%23DivX.E6.A0.BC.E5.BC.8F) **·** [DPX](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DDigital_Picture_Exchange%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [EVO](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DEnhanced_VOB%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [FLV](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FFlash_Video) **·** [GXF](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DGeneral_Exchange_Format%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [M2TS](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FM2TS) **·** [Matroska](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FMatroska) **·** [MPEG-PS](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DMPEG_program_stream%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [MPEG-TS](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DMPEG_transport_stream%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [MP4](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FMPEG-4_Part_14) **·** [MXF](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DMXF%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [Ogg](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FOgg) **·** [QuickTime](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FQuickTime) **·** [RealMedia](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FRealMedia) **·** [RIFF](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FResource_Interchange_File_Format) **·** [Smacker](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DSmacker_video%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) **·** [VOB](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DVOB%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1) |
| 只用于音频                                                   | [AIFF ](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FAIFF)**·** [AU](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fw%2Findex.php%3Ftitle%3DAu%E6%96%87%E4%BB%B6%E6%A0%BC%E5%BC%8F%26amp%3Baction%3Dedit%26amp%3Bredlink%3D1)**·** [WAV](http://www.open-open.com/home/link.php?url=http://zh.wikipedia.org%2Fzh-cn%2FWAV) |                                                              |

上面的表格，查看某个具体的codec，可以在中文的wiki中查找，但是英文的wiki咨询更为丰富，见下表 

| **[Multimedia](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMultimedia) [compression](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FData_compression) formats** |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [Video compression](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FVideo_compression) | [ISO](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FInternational_Organization_for_Standardization) /[IEC](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FInternational_Electrotechnical_Commission)   [MJPEG](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMotion_JPEG) **·** [Motion JPEG 2000](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FJPEG_2000%23Motion_JPEG_2000) **·** [MPEG-1](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMPEG-1) **·** [MPEG-2](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMPEG-2) ([Part 2](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FH.262%2FMPEG-2_Part_2) )**·** [MPEG-4](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMPEG-4) ([Part 2/ASP](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMPEG-4_Part_2) **·** [Part 10/AVC](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FH.264%2FMPEG-4_AVC) )**·** [HEVC](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FHigh_Efficiency_Video_Coding)    [ITU-T](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FITU-T)   [H.120](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FH.120) **·** [H.261](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FH.261) **·** [H.262](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FH.262%2FMPEG-2_Part_2) **·** [H.263](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FH.263) **·** [H.264](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FH.264%2FMPEG-4_AVC) **·** [HEVC](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FHigh_Efficiency_Video_Coding)    Others  [AMV](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FAMV_video_format) **·** [AVS](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FAudio_Video_Standard) **·** [Bink](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FBink_Video) **·** [CineForm](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FCineForm) **·** [Cinepak](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FCinepak) **·** [Dirac](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FDirac_%28codec%29) **·** [DV](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FDV) **·** [Indeo](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FIndeo) **·** [Microsoft Video 1](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMicrosoft_Video_1) **·** [OMS Video](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FOMS_Video) **·** [Pixlet](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FPixlet) **·** [RealVideo](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FRealVideo) **·** [RTVideo](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FRTVideo) **·** [SheerVideo](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FSheerVideo) **·** [Smacker](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FSmacker_video) **·** [Sorenson Video & Sorenson Spark](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FSorenson_codec) **·** [Theora](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FTheora) **·** [VC-1](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FVC-1) **·** [VP3](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FVP3) **·** [VP6](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FVP6) **·** [VP7](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FVP7) **·** [VP8](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FVP8) **·** [WMV](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FWindows_Media_Video) |
| [Audio compression](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FAudio_compression_%28data%29) | [ISO](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FInternational_Organization_for_Standardization) /[IEC](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FInternational_Electrotechnical_Commission)   [MPEG-1 Layer III (MP3)](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMP3) **·** [MPEG-1 Layer II](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMPEG-1_Audio_Layer_II) **·** [MPEG-1 Layer I](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMPEG-1_Audio_Layer_I) **·** [AAC](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FAdvanced_Audio_Coding) **·** [HE-AAC](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FHigh-Efficiency_Advanced_Audio_Coding) **·** [MPEG-4 ALS](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FAudio_Lossless_Coding) **·** [MPEG-4 SLS](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMPEG-4_SLS) **·** [MPEG-4 DST](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FDirect_Stream_Transfer%23DST) **·** [MPEG-4 HVXC](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FHarmonic_Vector_Excitation_Coding) **·** [MPEG-4 CELP](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMPEG-4_Part_3%23Subparts)    [ITU-T](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FITU-T)   [G.711](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FG.711) **·** [G.718](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FG.718) **·** [G.719](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FG.719) **·** [G.722](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FG.722) **·** [G.722.1](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FG.722.1) **·** [G.722.2](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FG.722.2) **·** [G.723](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FG.723) **·** [G.723.1](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FG.723.1) **·** [G.726](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FG.726) **·** [G.728](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FG.728) **·** [G.729](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FG.729) **·** [G.729.1](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FG.729.1)    Others  [AC-3](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FDolby_Digital) **·** [AMR](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FAdaptive_Multi-Rate_audio_codec) **·** [AMR-WB](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FAdaptive_Multi-Rate_Wideband) **·** [AMR-WB+](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FExtended_Adaptive_Multi-Rate_-_Wideband) **·** [Apple Lossless](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FApple_Lossless) **·** [ATRAC](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FAdaptive_Transform_Acoustic_Coding) **·** [DRA](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FDynamic_Resolution_Adaptation) **·** [DTS](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FDTS_%28sound_system%29) **·** [FLAC](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FFree_Lossless_Audio_Codec) **·** [GSM-HR](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FHalf_Rate) **·** [GSM-FR](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FFull_Rate) **·** [GSM-EFR](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FEnhanced_Full_Rate) **·** [iLBC](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FInternet_Low_Bit_Rate_Codec) **·** [Monkey's Audio](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMonkey%27s_Audio) **·** [TTA](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FTTA_%28codec%29) (True Audio)**·** [MT9](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMT9) **·** [μ-law](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2F%CE%9C-law_algorithm) **·** [Musepack](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMusepack) **·** [Nellymoser](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FNellymoser_Asao_Codec) **·** [OptimFROG](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FOptimFROG) **·** [OSQ](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FOriginal_Sound_Quality) **·** [RealAudio](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FRealAudio) **·** [RTAudio](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FRTAudio) **·** [SD2](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FDigidesign%23Sound_Designer_File_Formats) **·** [SHN](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FShorten) **·** [SILK](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FSILK) **·** [Siren](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FSiren_Codec) **·** [Speex](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FSpeex) **·** [TwinVQ](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FTwinVQ) **·** [Vorbis](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FVorbis) **·** [WavPack](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FWavPack) **·** [WMA](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FWindows_Media_Audio) |
| [Image compression](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FImage_compression) | [ISO](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FInternational_Organization_for_Standardization) /[IEC](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FInternational_Electrotechnical_Commission) /[ITU-T](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FITU-T)   [JPEG](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FJPEG) **·** [JPEG 2000](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FJPEG_2000) **·** [JPEG XR](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FJPEG_XR) **·** [lossless JPEG](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FLossless_JPEG) **·** [JBIG](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FJBIG) **·** [JBIG2](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FJBIG2) **·** [PNG](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FPortable_Network_Graphics) **·** [WBMP](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FWireless_Application_Protocol_Bitmap_Format)    Others  [APNG](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FAPNG) **·** [BMP](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FBMP_file_format) **·** [DjVu](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FDjVu) **·** [EXR](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FOpenEXR) **·** [GIF](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FGraphics_Interchange_Format) **·** [ICER](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FICER) **·** [ILBM](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FILBM) **·** [MNG](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMultiple-image_Network_Graphics) **·** [PCX](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FPCX) **·** [PGF](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FProgressive_Graphics_File) **·** [TGA](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FTruevision_TGA) **·** [QTVR](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FQuickTime_VR) **·** [TIFF](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FTagged_Image_File_Format) |
| [Media containers](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FContainer_format_%28digital%29) | ISO/IEC  [MPEG-PS](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMPEG_program_stream) **·** [MPEG-TS](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMPEG_transport_stream) **·** [MPEG-4 Part 12](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMPEG-4_Part_12) /[JPEG 2000 Part 12](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FJPEG_2000%23Motion_JPEG_2000) **·** [MPEG-4 Part 14](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMPEG-4_Part_14)    ITU-T  [H.222.0](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMPEG-2%23Systems)    Others  [3GP and 3G2](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2F3GP_and_3G2) **·** [ASF](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FAdvanced_Systems_Format) **·** [AVI](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FAudio_Video_Interleave) **·** [Bink](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FBink_Video) **·** [DivX Media Format](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FDivX_Media_Format) **·** [DPX](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FDigital_Picture_Exchange) **·** [EVO](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FEnhanced_VOB) **·** [Flash Video](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FFlash_Video) **·** [GXF](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FGeneral_Exchange_Format) **·** [M2TS](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2F.m2ts) **·** [Matroska](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMatroska) **·** [MXF](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMaterial_Exchange_Format) **·** [Ogg](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FOgg) **·** [QuickTime](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FQuickTime) **·** [RealMedia](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FRealMedia) **·** [REDCODE RAW](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FREDCODE) **·** [RIFF](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FResource_Interchange_File_Format) **·** [Smacker](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FSmacker_video) **·** [MOD and TOD](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FMOD_and_TOD_%28video_format%29) **·** [VOB](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FVOB) **·** [WebM](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FWebM)    Audio only  [AIFF](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FAudio_Interchange_File_Format) **·** [AU](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FAu_file_format) **·** [WAV](http://www.open-open.com/home/link.php?url=http://en.wikipedia.org%2Fwiki%2FWAV) |

 

**通常会见到的码率控制模式有** 
 ABR [ Average Bitrate ]（平均目标码率模式） 
 CBR [ Constant Bitrate ]（固定码率模式） 
 2pass..3pass..npass（二次..三次..n次编码模式..严格来说也属于平均目标码率模式.但其码率 浮动较ABR高出不少.） 
 CRF [ Constant Ratefactor ] （固定码率系数模式） 
 QP [ Constant Quantizer ] （固定量化值模式） 

# ffmpeg中的时间单位

 **AV_TIME_BASE**

ffmpeg中的内部计时单位（时间基），ffmepg中的所有时间都是于它为一个单位，比如AVStream中的duration即以为着这个流的长度为duration个AV_TIME_BASE。AV_TIME_BASE定义为：

```
#define         AV_TIME_BASE   1000000
```

 

 **AV_TIME_BASE_Q**

ffmpeg内部时间基的分数表示，实际上它是AV_TIME_BASE的倒数。从它的定义能很清楚的看到这点：

```
#define         AV_TIME_BASE_Q   (AVRational){1, AV_TIME_BASE}
```

 

AVRatioal的定义如下：

```
typedef struct AVRational{
int num; //numerator
int den; //denominator
} AVRational;
```

ffmpeg提供了一个把AVRatioal结构转换成double的函数：

```
static inline double av_q2d(AVRational a)｛
/**
* Convert rational to double.
* @param a rational to convert
**/
    return a.num / (double) a.den;
}
```


现在可以根据pts来计算一桢在整个视频中的时间位置：

```
timestamp(秒) = pts * av_q2d(st->time_base)
 
```

计算视频长度的方法：

```
time(秒) = st->duration * av_q2d(st->time_base)
 
```

这里的st是一个AVStream对象指针。

**时间基转换公式**

- timestamp(ffmpeg内部时间戳) = AV_TIME_BASE * time(秒)
- time(秒) = AV_TIME_BASE_Q * timestamp(ffmpeg内部时间戳)

所以当需要把视频跳转到N秒的时候可以使用下面的方法：

```
int64_t timestamp = N * AV_TIME_BASE; 
2
av_seek_frame(fmtctx, index_of_video, timestamp, AVSEEK_FLAG_BACKWARD);
```

ffmpeg同样为我们提供了不同时间基之间的转换函数：

```
int64_t av_rescale_q(int64_t a, AVRational bq, AVRational cq)
```

这个函数的作用是计算a * bq / cq，来把时间戳从一个时基调整到另外一个时基。在进行时基转换的时候，我们应该首选这个函数，因为它可以避免溢出的情况发生。



**time_base**

1. `AVStream`的`time_base`的单位是秒。每种格式的`time_base`的值不一样，根据采样来计算，比如`mpeg`的`pts`、`dts`都是以`90kHz`来采样的，所以采样间隔就是`1/900000`秒。
2. `AVCodecContext`的`time_base`单位同样为秒，不过精度没有`AVStream->time_base`高，大小为`1/framerate`。
3. `AVPacket`下的`pts`和`dts`以`AVStream->time_base`为单位(数值比较大)，时间间隔就是`AVStream->time_base`。
4. `AVFrame`里面的`pkt_pts`和`pkt_dts`是拷贝自AVPacket，同样以`AVStream->time_base`为单位；而`pts`是为输出(显示)准备的，以`AVCodecContex->time_base`为单位。
5. 输入流`InputStream`下的`pts`和`dts`以`AV_TIME_BASE`为单位(微秒)，至于为什么要转化为微秒，可能是为了避免使用浮点数。
6. 输出流`OutputStream`涉及音视频同步，结构和`InputStream`不同，暂时只作记录，不分析。

**各个time_base之前的转换**

**ffmpeg**提供`av_rescale_q`函数用于`time_base`之间转换，`av_rescale_q(a,b,c)`作用相当于执行`a*b/c`，通过设置`b,c`的值，可以很方便的实现`time_base`之间转换。

 **其他**

`AVFrame->pts`和`AVPacket->pts`、`AVPacket->dts`的值，在解码/编码后，会经历短暂的time_base不匹配的情况：

1. 解码后，`decoded_frame->pts`的值使用`AVStream->time_base`为单位，后在`AVFilter`里面转换成以`AVCodecContext->time_base`为单位。
2. 编码后，`pkt.pts`、`pkt.dts`使用`AVCodecContext->time_base`为单位，后通过调用`"av_packet_rescale_ts"`转换为`AVStream->time_base`为单位。

*知识点1：av_q2d(AVRational a)函数
    av_q2d(AVRational);该函数负责把AVRational结构转换成double，通过这个函数可以计算出某一帧在视频中的时间位置
    timestamp(秒) = pts * av_q2d(st->time_base);
    计算视频长度的方法：
    time(秒) = st->duration * av_q2d(st->time_base);

*知识点2：av_rescale_q(int64_t a, AVRational bq, AVRational cq)函数
    这个函数的作用是计算a*bq / cq来把时间戳从一个时间基调整到另外一个时间基。在进行时间基转换的时候，应该首先这个函数，因为它可以避免溢出的情况发生

*知识点3：ffmpeg内部的时间与标准的时间转换方法：
    timestamp(ffmpeg内部的时间戳) = AV_TIME_BASE * time(秒)
    time(秒) = AV_TIME_BASE_Q * timestamp(ffmpeg内部的时间戳)
*知识点5：不同的时间基
    现实中不同的封装格式，timebase是不一样的。另外，整个转码过程，不同的数据状态对应的时间基也不一致。还是拿mpegts封装格式25fps来
    说（只说视频，音频大致一样，但也略有不同）。非压缩时候的数据（即YUV或者其它），在ffmpeg中对应的结构体为AVFrame,它的时间基为AVRational{1,25}。
    压缩后的数据（对应的结构体为AVPacket）对应的时间基为AVRational{1,90000}



# FFMpeg滤镜中英文对照

http://ffmpeg.org/ffmpeg-filters.html

http://www.mamicode.com/info-detail-1208970.html

http://www.mamicode.com/info-detail-1208951.html

```
    FFMpeg ver 20160213-git-588e2e3 滤镜中英文对照 2016.02.17 by 1CM
     
    T.. = Timeline support
          支持时间轴
    .S. = Slice threading
          分段线程
    ..C = Command support
          支持命令传送
    A = Audio input/output
        音频 输入/输出
    V = Video input/output
        视频 输入/输出
    N = Dynamic number and/or type of input/output
        可输入动态值
    | = Source or sink filter
        源或场景过滤
     
    Audio Filters
    音频滤镜
     
     ... acompressor       A->A       Audio compressor.
                                      压缩音频.
     ... acrossfade        AA->A      Cross fade two input audio streams.
                                      交叉混合输入的两个音频流.
     T.. adelay            A->A       Delay one or more audio channels.
                                      延迟单个或多个音频通道.
     ... aecho             A->A       Add echoing to the audio.
                                      音频上追加回波.
     ... aemphasis         A->A       Audio emphasis.
                                      音频补偿.
     ... aeval             A->A       Filter audio signal according to a specified expression.
                                      根据指定的表达式修改音频信号.
     T.. afade             A->A       Fade in/out input audio.
                                      淡入/淡出 输入的音频.
     ... afftfilt          A->A       Apply arbitrary expressions to samples in frequency domain.
                                      将任意表达式应用到采样频域.
     ... aformat           A->A       Convert the input audio to one of the specified formats.
                                      指定格式转换输入的音频.
     ... agate             A->A       Audio gate.
                                      音频通道.
     ... ainterleave       N->A       Temporally interleave audio inputs.
                                      时间交叠输入音频.
     ... alimiter          A->A       Audio lookahead limiter.
                                      音频超前限制.
     ... allpass           A->A       Apply a two-pole all-pass filter.
                                      应用到一个两极全通滤镜.
     ... amerge            N->A       Merge two or more audio streams into a single multi-channel stream.
                                      两个或两个以上的音频流合并到一个多通道流.
     T.. ametadata         A->A       Manipulate audio frame metadata.
                                      操控音频帧的元数据.
     ... amix              N->A       Audio mixing.
                                      多个输入音频混合到单个音频输出.
     ..C anequalizer       A->N       Apply high-order audio parametric multi band equalizer.
                                      应用到每个通道高阶参数多波段均衡器.
     ... anull             A->A       Pass the source unchanged to the output.
                                      不改变音频源进行输出.
     T.. apad              A->A       Pad audio with silence.
                                      无声填充模板.
     ... aperms            A->A       Set permissions for the output audio frame.
                                      允许设置输出的音频帧.
     ... aphaser           A->A       Add a phasing effect to the audio.
                                      给输入音频添加调相效果.
     ... apulsator         A->A       Audio pulsator.
                                      音频震动器.
     ... arealtime         A->A       Slow down filtering to match realtime.
                                      减慢过滤作用,近似实时匹配.
     ... aresample         A->A       Resample audio data.
                                      重新采样音频数据.
     ... areverse          A->A       Reverse an audio clip.
                                      反转音频素材.
     ... aselect           A->N       Select audio frames to pass in output.
                                      选择音频帧赋予输出.
     ... asendcmd          A->A       Send commands to filters.
                                      给滤镜发送命令,必须插入到两个音频之间,只对具有该功能的滤镜命令有效.
     ... asetnsamples      A->A       Set the number of samples for each output audio frames.
                                      设置每个输出音频帧的采样数.
     ... asetpts           A->A       Set PTS for the output audio frame.
                                      设置输出音频的表示时间戳(PTS).
     ... asetrate          A->A       Change the sample rate without altering the data.
                                      设置采样率,但不改变PCM数据.
     ... asettb            A->A       Set timebase for the audio output link.
                                      设置时间轴用于音频输出帧的时间戳.
     ... ashowinfo         A->A       Show textual information for each audio frame.
                                      显示每个音频帧的文本信息.
     ... asplit            A->N       Pass on the audio input to N audio outputs.
                                      输入的音频分配给N个相同的输出.
     ... astats            A->A       Show time domain statistics about audio frames.
                                      显示音频帧的时域统计信息.
     ..C astreamselect     N->N       Select audio streams.
                                      多个输入音频流中选择一个音频流,若干个具有相同时间长度的媒体有效.
     ..C atempo            A->A       Adjust audio tempo.
                                      调整音频播放速度, 其范围是0.5-2.0.
     ... atrim             A->A       Pick one continuous section from the input, drop the rest.
                                      从输入音频中挑选连续的组成部分,一直到结束.
     ... bandpass          A->A       Apply a two-pole Butterworth band-pass filter.
                                      应用到一个两极巴特沃斯带通滤波器的主要频率.
     ... bandreject        A->A       Apply a two-pole Butterworth band-reject filter.
                                      应用到一个两极巴特沃斯带阻滤波器的主要频率.
     ... bass              A->A       Boost or cut lower frequencies.
                                      增加或减少低频.
     ... biquad            A->A       Apply a biquad IIR filter with the given coefficients.
                                      应用到双二次滤镜的特定系数.
     ... bs2b              A->A       Bauer stereo-to-binaural filter.
                                      鲍尔立体声双声道的转换,适合用耳机听立体声音频.
     ... channelmap        A->A       Remap audio channels.
                                      将输入音频通道重新映射到新的位置.
     ... channelsplit      A->N       Split audio into per-channel streams.
                                      输入音频流的每个音频通道分为不同的输出流.
     ... chorus            A->A       Add a chorus effect to the audio.
                                      给音频添加合唱效果.
     ... compand           A->A       Compress or expand audio dynamic range.
                                      压缩或展开音频的动态范围.
     ... compensationdelay A->A       Audio Compensation Delay Line.
                                      给音频补偿延迟线.
     T.. dcshift           A->A       Apply a DC shift to the audio.
                                      应用到DC偏置(可能由硬件问题引起的录音通路)的音频.
     ... dynaudnorm        A->A       Dynamic Audio Normalizer.
                                      动态音频的标准化.
     ... earwax            A->A       Widen the stereo image.
                                      扩展到用耳机听到立体感.
     ... ebur128           A->N       EBU R128 scanner.
                                      EBU R128 音频可视化扫描滤镜.
     ... equalizer         A->A       Apply two-pole peaking equalization (EQ) filter.
                                      应用到两极峰值均衡器(EQ)滤镜.
     ... extrastereo       A->A       Increase difference between stereo audio channels.
                                      给左右音频通道线性增加某种"现场"回放效果.
     ... flanger           A->A       Apply a flanging effect to the audio.
                                      翻边效果应用到音频中.
     ... highpass          A->A       Apply a high-pass filter with 3dB point frequency.
                                      应用到3db点频率的高通滤镜.
     ... join              N->A       Join multiple audio streams into multi-channel output.
                                      多输入音频流连接到一个多通道输出流.
     ... lowpass           A->A       Apply a low-pass filter with 3dB point frequency.
                                      应用到3db点频率的低通滤镜.
     ... pan               A->A       Remix channels with coefficients (panning).
                                      混合特定增益电平的通道(填充).
     ... replaygain        A->A       ReplayGain scanner.
                                      显示增益和峰值的扫描滤镜.
     ... sidechaincompress AA->A      Sidechain compressor.
                                      侧链压缩器,需要两个输入流,返回一个输出流.
     ... sidechaingate     AA->A      Audio sidechain gate.
                                      音频侧链的增益.
     ... silencedetect     A->A       Detect silence.
                                      检测音频流中的无声部分.
     ... silenceremove     A->A       Remove silence.
                                      删除无声部分,从开始到结束.
     ... stereotools       A->A       Apply various stereo tools.
                                      应用到不同立体感的功能.
     ... stereowiden       A->A       Apply stereo widening effect.
                                      应用到扩展立体效果.
     ... treble            A->A       Boost or cut upper frequencies.
                                      增加或减少上频率.
     ... tremolo           A->A       Apply tremolo effect.
                                      应用到震音效果,有一点回音效果.
     ... vibrato           A->A       Apply vibrato effect.
                                      应用到颤音效果.
     T.C volume            A->A       Change input volume.
                                      改变输入音频的音量.
     ... volumedetect      A->A       Detect audio volume.
                                      检测输入音频的音量.
     ... aevalsrc          |->A       Generate an audio signal generated by an expression.
                                      根据指定的表达式生成一个音频信号.
     ... anoisesrc         |->A       Generate a noise audio signal.
                                      生成一个噪声音频信号.
     ... anullsrc          |->A       Null audio source, return empty audio frames.
                                      生成无声音频源,返回未处理的空音频帧.
     ... sine              |->A       Generate sine wave audio signal.
                                      生成一个正弦波音频信号.
     ... anullsink         A->|       Do absolutely nothing with the input audio.
                                      无声音频接收器,与输入音频无关.
     ... adrawgraph        A->V       Draw a graph using input audio metadata.
                                      利用音频的元数据画曲线图.
     ... ahistogram        A->V       Convert input audio to histogram video output.
                                      输入音频转换为视频输出,显示音量直方图.
     ... aphasemeter       A->V       Convert input audio to phase meter video output.
                                      输入音频转换为相位表视频输出.
     ... avectorscope      A->V       Convert input audio to vectorscope video output.
                                      输入音频转换为矢量色度显示视频输出.
     ... showcqt           A->V       Convert input audio to a CQT (Constant/Clamped Q Transform) spectrum video output.
                                      输入音频转换为 固定/固支 Q 变换(CQT) 频谱视频输出.
     ... showfreqs         A->V       Convert input audio to a frequencies video output.
                                      输入音频转换为音频功率谱视频输出.
     ... showspectrum      A->V       Convert input audio to a spectrum video output.
                                      输入音频转换为音频频谱视频输出.
     ... showspectrumpic   A->V       Convert input audio to a spectrum video output single picture.
                                      输入音频转换为单张音谱图片.
     ... showvolume        A->V       Convert input audio volume to video output.
                                      输入音频音量转换为视频输出.
     ... showwaves         A->V       Convert input audio to a video output.
                                      输入音频转换为波形视频输出.
     ... showwavespic      A->V       Convert input audio to a video output single picture.
                                      输入音频转换为单张波形图片.
     ... spectrumsynth     VV->A      Convert input spectrum videos to audio output.
                                      输入视频谱转换为音频输出.
     ... abuffer           |->A       Buffer audio frames, and make them accessible to the filterchain.
                                      缓冲音频帧,并用于滤镜链.
     ... abuffersink       A->|       Buffer audio frames, and make them available to the end of the filter graph.
                                      缓冲音频帧,并用于滤镜图的结束.
     ... afifo             A->A       Buffer input frames and send them when they are requested.
                                      缓冲输入帧,若需求时.
     ... amovie            |->N       Read audio from a movie source.
                                      从视频源读入音频.
     
    Video Filters
    视频滤镜
     
     ... alphaextract      V->N       Extract an alpha channel as a grayscale image component.
                                      从灰度级测视图中提取阿尔法α通道分量.
     ... alphamerge        VV->V      Copy the luma value of the second input into the alpha channel of the first input.
                                      使用第一个输入视频的阿尔法α通道分量,添加或替换的第二个输入视频亮度值.
     TS. atadenoise        V->V       Apply an Adaptive Temporal Averaging Denoiser.
                                      自适应时间平均降噪功能应用在输入的视频.
     ... ass               V->V       Render ASS subtitles onto input video using the libass library.
                                      使用libass程序库给输入视频渲染ASS字幕.
     T.. bbox              V->V       Compute bounding box for each frame.
                                      视频的每一个帧上计算边界框.
     ... blackdetect       V->V       Detect video intervals that are (almost) black.
                                      检测视频中完全(几乎)黑色的时间间隔.
     ... blackframe        V->V       Detect frames that are (almost) black.
                                      检测完全(几乎)黑色的帧.
     TS. blend             VV->V      Blend two video frames into each other.
                                      两个视频帧混合到另一个帧上.
     T.. boxblur           V->V       Blur the input.
                                      模糊处理输入视频.
     TS. chromakey         V->V       Turns a certain color into transparency. Operates on YUV colors.
                                      在YUV颜色空间中针对一些颜色做透明处理,应用与抠图功能,比 colorkey 滤镜边界更柔和.
     T.. codecview         V->V       Visualize information about some codecs.
                                      导出一些解码器的可视化信息.
     T.. colorbalance      V->V       Adjust the color balance.
                                      修改输入帧的三原色(红、绿、蓝)信号亮度.
     T.. colorchannelmixer V->V       Adjust colors by mixing color channels.
                                      调整输入视频帧的混合颜色通道.
     TS. colorkey          V->V       Turns a certain color into transparency. Operates on RGB colors.
                                      在RGB颜色空间中针对一些颜色做透明处理,边界较为生硬.
     T.. colorlevels       V->V       Adjust the color levels.
                                      调整输入视频帧的颜色信号电平.
     TS. colormatrix       V->V       Convert color matrix.
                                      转换颜色矩阵.
     T.. convolution       V->V       Apply convolution filter.
                                      使用卷积3x3或5x5滤镜,适用于锐化,模糊,边缘增强,边缘检测和浮雕等处理.
     ... copy              V->V       Copy the input video unchanged to the output.
                                      复制输入视频,原封不动输出,主要是用于测试目的.
     ... cover_rect        V->V       Find and cover a user specified object.
                                      查找并覆盖用户指定的矩形对象.
     ..C crop              V->V       Crop the input video to given dimensions.
                                      剪切输入视频显示区域,并给于新的尺寸.
     T.. cropdetect        V->V       Auto-detect crop size.
                                      自动检测剪切大小.
     TS. curves            V->V       Adjust components curves.
                                      利用曲线功能调整颜色分量,也可以利用图象处理软件的曲线文件来处理颜色.
     TS. dctdnoiz          V->V       Denoise frames using 2D DCT.
                                      使用二维频域过滤(2D DCT)对帧进行降噪处理.
     TS. deband            V->V       Debands video, Remove banding artifacts from input video.
                                      从输入视频中移除带状伪像.
     ... decimate          N->V       Decimate frames (post field matching filter).
                                      定期删除重复的帧(后场匹配滤镜).
     T.. deflate           V->V       Apply deflate effect.
                                      适用于紧缩效果.
     ... dejudder          V->V       Remove judder produced by pullup.
                                      删除动作产生的部分颤抖.
     T.. delogo            V->V       Remove logo from input video.
                                      对指定区域做模糊处理,比如能移除输入视频中的标识.
     ... deshake           V->V       Stabilize shaky video.
                                      试图修改水平或垂直的移位,降低颤抖让视频更稳定,这个滤镜有助于减小手持相机抖动影响.
     ... detelecine        V->V       Apply an inverse telecine pattern.
                                      适用于电视电影的精确反向操作,颜色边界有锯齿效果.
     T.. dilation          V->V       Apply dilation effect.
                                      膨胀效果应用于视频.
     T.. displace          VVV->V     Displace pixels.
                                      移走像素,需要三个视频输入流和一个视频输出流,第一个输入源,第二和第三个输入位移的映射.
     T.. drawbox           V->V       Draw a colored box on the input video.
                                      输入视频图像上绘制彩色的矩形区域.
     ... drawgraph         V->V       Draw a graph using input video metadata.
                                      利用输入视频的元数据绘制图表.
     T.. drawgrid          V->V       Draw a colored grid on the input video.
                                      在输入视频上绘制彩色网格.
     T.C drawtext          V->V       Draw text on top of video frames using libfreetype library.
                                      使用 libfreetype 程序库,在顶层帧上绘制文本字符串,文本内容可从指定文件中读取.
     T.. edgedetect        V->V       Detect and draw edge.
                                      检测并绘制边缘.
     ... elbg              V->V       Apply posterize effect, using the ELBG algorithm.
                                      使用增强型LBG(ELBG)算法,用于多色调分色印效果.
     ..C eq                V->V       Adjust brightness, contrast, gamma, and saturation.
                                      调整亮度、对比度、灰度和饱和度.
     T.. erosion           V->V       Apply erosion effect.
                                      侵蚀效果应用于视频,类似油画处理.
     ... extractplanes     V->N       Extract planes as grayscale frames.
                                      从输入视频流中提取颜色通道分量用在单独灰度视频流的帧上.
     .S. fade              V->V       Fade in/out input video.
                                      适用于输入视频的淡入/淡出效果.
     ... fftfilt           V->V       Apply arbitrary expressions to pixels in frequency domain.
                                      频域内将任意表达式用于采样的像素集.
     ... field             V->V       Extract a field from the input video.
                                      使用步进算法,从输入视频里的隔行图像中提取单场.
     ... fieldmatch        N->V       Field matching for inverse telecine.
                                      场匹配滤镜适用于电视电影的反向操作.
     T.. fieldorder        V->V       Set the field order.
                                      改变输入视频的场顺序.
     ... find_rect         V->V       Find a user specified object.
                                      寻找用户指定的矩形区域.
     ... format            V->V       Convert the input video to one of the specified pixel formats.
                                      输入视频转换为指定的像素格式.
     ... fps               V->V       Force constant framerate.
                                      强制设定固定帧频.
     ... framepack         VV->V      Generate a frame packed stereoscopic video.
                                      生成帧叠加的立体视频.
     ... framerate         V->V       Upsamples or downsamples progressive source between specified frame rates.
                                      上采样或下采样顺序渐进的视频源之间设定指定帧频.
     T.. framestep         V->V       Select one frame every N frames.
                                      每 N 个帧中选一个帧,设置帧步.
     ... frei0r            V->V       Apply a frei0r effect.
                                      使用 frei0r 滤镜.
     T.. fspp              V->V       Apply Fast Simple Post-processing filter.
                                      用于快速和简单的后处理滤镜.
     T.. geq               V->V       Apply generic equation to each pixel.
                                      利用一般表达式改变每个像素点的特征.
     T.. gradfun           V->V       Debands video quickly using gradients.
                                      利用梯度快速移除带状伪像.
     TS. haldclut          VV->V      Adjust colors using a Hald CLUT.
                                      利用哈尔德查色表调整颜色.
     .S. hflip             V->V       Horizontally flip the input video.
                                      水平翻转显示输入视频.
     T.. histeq            V->V       Apply global color histogram equalization.
                                      适用于全局颜色直方图均衡化.
     ... histogram         V->V       Compute and draw a histogram.
                                      计算并绘制颜色分布直方图.
     T.. hqdn3d            V->V       Apply a High Quality 3D Denoiser.
                                      使用高质量三维降噪滤镜.
     .S. hqx               V->V       Scale the input by 2, 3 or 4 using the hq*x magnification algorithm.
                                      利用高质量放大算法缩放视频显示大小,可输入2,3或4.
     ... hstack            N->V       Stack video inputs horizontally.
                                      把若干个输入视频合并到一个水平显示的输出视频.
     T.C hue               V->V       Adjust the hue and saturation of the input video.
                                      调整输入视频的色相和饱和度.
     ... idet              V->V       Interlace detect Filter.
                                      检测视频的交叉类型滤镜.
     T.. il                V->V       Deinterleave or interleave fields.
                                      允许处理不交叉的隔行图像场.
     T.. inflate           V->V       Apply inflate effect.
                                      膨胀效果用于视频.
     ... interlace         V->V       Convert progressive video into interlaced.
                                      转化为分段视频用于隔行处理,颜色边界有锯齿效果.
     ... interleave        N->V       Temporally interleave video inputs.
                                      能执行时间场交叉的各种类型.
     ... kerndeint         V->V       Apply kernel deinterlacing to the input.
                                      对输入的视频进行内核反交叉处理.
     .S. lenscorrection    V->V       Rectify the image by correcting for lens distortion.
                                      矫正图像用于校正透镜畸变.
     TS. lut3d             V->V       Adjust colors using a 3D LUT.
                                      利用三维查色表调整颜色.
     T.. lut               V->V       Compute and apply a lookup table to the RGB/YUV input video.
                                      利用查表计算处理 RGB/YUV 格式输入的视频.
     T.. lutrgb            V->V       Compute and apply a lookup table to the RGB input video.
                                      利用查表计算处理 RGB 格式输入的视频.
     T.. lutyuv            V->V       Compute and apply a lookup table to the YUV input video.
                                      利用查表计算处理 YUV 格式输入的视频.
     T.. maskedmerge       VVV->V     Merge first stream with second stream using third stream as mask.
                                      合并前二个输入视频,掩模到第三个输入视频,透明合并三个视频.
     ... mcdeint           V->V       Apply motion compensating deinterlacing.
                                      适用于运动补偿反交叉.
     ... mergeplanes       N->V       Merge planes.
                                      合并多个视频流的颜色通道分量.
     T.. metadata          V->V       Manipulate video frame metadata.
                                      操作视频帧的元数据,用于调试.
     ... mpdecimate        V->V       Remove near-duplicate frames.
                                      移除近似重复的帧.
     T.. negate            V->V       Negate input video.
                                      取消输入视频的阿尔法通道分量,滤镜效果类似底片.
     T.. nnedi             V->V       Apply neural network edge directed interpolation intra-only deinterlacer.
                                      使用神经网络边缘插值法进行反隔行处理,需要加权重的二进制文件.
     ... noformat          V->V       Force libavfilter not to use any of the specified pixel formats for the input to the next filter.
                                      取消指定的像素格式,用于下一个滤镜.
     TS. noise             V->V       Add noise.
                                      视频输入帧上添加噪声.
     ... null              V->V       Pass the source unchanged to the output.
                                      不改变视频源进行输出.
     T.C overlay           VV->V      Overlay a video source on top of the input.
                                      把一个视频覆盖到另一个视频上面,需要两个输入和一个输出.
     T.. owdenoise         V->V       Denoise using wavelets.
                                      利用小波降噪法进行降噪处理.
     ... pad               V->V       Pad the input video.
                                      给输入视频添加填充新的显示区域.
     ... palettegen        V->V       Find the optimal palette for a given stream.
                                      生成最佳调色板,用于给定的视频流.
     ... paletteuse        VV->V      Use a palette to downsample an input video stream.
                                      下采样输入视频流中使用调色板,适用于生成 GIF 动态图.
     ... perms             V->V       Set permissions for the output video frame.
                                      给输出视频帧设置读/写权限.
     TS. perspective       V->V       Correct the perspective of video.
                                      校正视频的透视.
     T.. phase             V->V       Phase shift fields.
                                      对隔行视频延迟单场时间,便于场序的变化.
     ... pixdesctest       V->V       Test pixel format definitions.
                                      像素格式描述符测试滤镜,主要用于内部测试.
     T.C pp                V->V       Filter video using libpostproc.
                                      使用 libpostproc 后处理程序库进行过滤.
     T.. pp7               V->V       Apply Postprocessing 7 filter.
                                      使用后处理滤镜7.
     ... psnr              VV->V      Calculate the PSNR between two video streams.
                                      计算两个视频流之间的峰值信噪比(PSNR).
     ... pullup            V->V       Pullup from field sequence to frames.
                                      折叠场序用于输出帧,退回到电视电影效果.
     T.. qp                V->V       Change video quantization parameters.
                                      改变视频量化参数(QP).
     ... random            V->V       Return random frames.
                                      从内部缓存刷新出视频帧的随机帧.
     ... realtime          V->V       Slow down filtering to match realtime.
                                      减慢过滤速度,接近实时效果.
     TS. removegrain       V->V       Remove grain.
                                      移除纹理,对步进视频进行降噪处理.
     T.. removelogo        V->V       Remove a TV logo based on a mask image.
                                      利用掩模图像移除电视徽标,掩模图像的大小必须与视频相同,黑色是透明.
     ... repeatfields      V->V       Hard repeat fields based on MPEG repeat field flag.
                                      根据运动图象专家组(MPEG)重复场标志,硬执行重复场.
     ... reverse           V->V       Reverse a clip.
                                      倒放一段视频片段,需要把整个片段装入内存缓冲区.
     TSC rotate            V->V       Rotate the input image.
                                      任意角度旋转视频,用弧度表示的单位.
     T.. sab               V->V       Apply shape adaptive blur.
                                      形状自适应模糊滤镜.
     ..C scale             V->V       Scale the input video size and/or convert the image format.
                                      缩放输入视频的尺寸并/或改变图像格式,使用libswscale库.
     ..C scale2ref         VV->VV     Scale the input video size and/or convert the image format to the given reference.
                                      缩放输入视频的尺寸并/或改变图像格式用于引用视频,使用libswscale库.
     ... select            V->N       Select video frames to pass in output.
                                      选择视频帧用于下一个滤镜.
     TS. selectivecolor    V->V       Apply CMYK adjustments to specific color ranges.
                                      利用青色,品红色,黄色和黑色(CMYK)调整特定范围的颜色.
     ... sendcmd           V->V       Send commands to filters.
                                      给滤镜发送命令,必须插入到两个视频之间,只对具有该功能的滤镜命令有效.
     ... separatefields    V->V       Split input video frames into fields.
                                      分解输入视频帧进场,产生一个新的一半高度剪辑帧.
     ... setdar            V->V       Set the frame display aspect ratio.
                                      设置视频的显示纵横比.
     ... setfield          V->V       Force field for the output video frame.
                                      改变输出视频帧的属性,不改变视频帧的数据.
     ... setpts            V->V       Set PTS for the output video frame.
                                      设置输出视频帧的显示时间戳(PTS),可以用于快放或慢放等.
     ... setsar            V->V       Set the pixel sample aspect ratio.
                                      设置像素采样纵横比.
     ... settb             V->V       Set timebase for the video output link.
                                      设置时间轴用于视频输出帧的时间戳,主要用于测试时间轴配置.
     ... showinfo          V->V       Show textual information for each video frame.
                                      显示每个视频帧的文本信息.
     T.. showpalette       V->V       Display frame palette.
                                      显示每一帧的 256 色调色板.
     T.. shuffleframes     V->V       Shuffle video frames.
                                      打乱视频帧,重新排序和/或重复视频帧.
     ... shuffleplanes     V->V       Shuffle video planes.
                                      打乱视频映射平面,重新排序和/或重复视频映射平面.
     .S. signalstats       V->V       Generate statistics from video analysis.
                                      分析视频过程中生成统计信息.
     T.. smartblur         V->V       Blur the input video without impacting the outlines.
                                      模糊处理输入视频而不影响轮廓.
     ... split             V->N       Pass on the input to N video outputs.
                                      输入的视频分配给N个相同的视频输出.
     T.C spp               V->V       Apply a simple post processing filter.
                                      简单的后处理滤镜,设置压缩品质对视频进行压缩.
     ... ssim              VV->V      Calculate the SSIM between two video streams.
                                      计算两个输入视频之间的结构相似度(SSIM).
     .S. stereo3d          V->V       Convert video stereoscopic 3D view.
                                      视频转换成具有不同立体图像格式的三维视觉视频.
     ..C streamselect      N->N       Select video streams
                                      多个输入视频流中选择一个视频流,若干个具有相同时间长度的媒体有效.
     ... subtitles         V->V       Render text subtitles onto input video using the libass library.
                                      使用 libass 程序库输入视频上绘制字幕.
     ... super2xsai        V->V       Scale the input by 2x using the Super2xSaI pixel art algorithm.
                                      利用像素艺术扩展算法把输入视频平滑放大两倍.
     T.. swaprect          V->V       Swap 2 rectangular objects in video.
                                      视频流中交换两个矩形对象.
     ... swapuv            V->V       Swap U and V components.
                                      交换 U 和 V 映射平面分量.
     .S. tblend            V->V       Blend successive frames.
                                      两个视频帧混合到另一个帧上.
     ... telecine          V->V       Apply a telecine pattern.
                                      使用电视电影模式,颜色边界有锯齿效果.
     ... thumbnail         V->V       Select the most representative frame in a given sequence of consecutive frames.
                                      在给定的连续帧序列中选择具有代表性帧.
     ... tile              V->V       Tile several successive frames together.
                                      瓦状布局若干个连续的帧,类似视频缩略图.
     ... tinterlace        V->V       Perform temporal field interlacing.
                                      使用不同的隔行模式处理每一个帧.
     .S. transpose         V->V       Transpose input video.
                                      翻转输入视频,默认垂直翻转.
     ... trim              V->V       Pick one continuous section from the input, drop the rest.
                                      从输入视频中挑选连续的组成部分,一直到结束.
     T.. unsharp           V->V       Sharpen or blur the input video.
                                      锐化或模糊处理输入视频.
     T.. uspp              V->V       Apply Ultra Simple / Slow Post-processing filter.
                                      超慢/简单的后处理滤镜,设置压缩品质对视频进行压缩.
     ... vectorscope       V->V       Video vectorscope.
                                      显示输入视频的两个颜色分量值的二维图(矢量显示).
     ... vflip             V->V       Flip the input video vertically.
                                      垂直翻转显示输入视频.
     ... vidstabdetect     V->V       Extract relative transformations,for stabilization.
                                      提取视频的相对地变化,绘制矩形图矩阵内的箭头方向来显示变化趋势.
     ... vidstabtransform  V->V       Video stabilization/deshaking.
                                      平滑/反锐化处理视频.
     T.. vignette          V->V       Make or reverse a vignette effect.
                                      生成或扭转镜头自然渐晕效果.
     ... vstack            N->V       Stack video inputs vertically.
                                      把若干个输入视频垂直放置,所有视频的像素格式和宽度必须相同.
     TS. w3fdif            V->V       Apply Martin Weston three field deinterlace.
                                      使用马丁韦斯顿三场反隔行滤镜。
     ... waveform          V->V       Video waveform monitor.
                                      视频波形监视器.
     .S. xbr               V->V       Scale the input using xBR algorithm.
                                      应用xBR算法放大输入视频,默认是放大三倍.
     TS. yadif             V->V       Deinterlace the input image.
                                      对输入图像进行反隔行处理.
     T.. zoompan           V->V       Apply Zoom & Pan effect.
                                      用于缩放和填充效果.
     ..C zscale            V->V       Apply resizing, colorspace and bit depth conversion.
                                      用于重新调整大小,改变色隙和色彩深度.
     ... allrgb            |->V       Generate all RGB colors.
                                      生成大小为 4096x4096 的包含所有 RGB 颜色表,需要大量内存.
     ... allyuv            |->V       Generate all yuv colors.
                                      生成大小为 4096x4096 的包含所有 yuv 颜色表,需要大量内存.
     ... cellauto          |->V       Create pattern generated by an elementary cellular automaton.
                                      利用初级多孔自动生成器创建一个图案,指定模式生成无数小三角形矩阵.
     ..C color             |->V       Provide an uniformly colored input.
                                      提供了一个单色输入视频源.
     ... frei0r_src        |->V       Generate a frei0r source.
                                      提供frei0r接口,frei0r是ffmpeg的子滤镜.
     ... haldclutsrc       |->V       Provide an identity Hald CLUT.
                                      给哈尔德查色表源提供单位特征.
     ... life              |->V       Create life.
                                      生成随机花纹的图案.
     ... mandelbrot        |->V       Render a Mandelbrot fractal.
                                      生成一个曼德尔勃特集合分形,逐渐放大到指定点.
     ... mptestsrc         |->V       Generate various test pattern.
                                      生成各种测试图案,静/动态小方块矩阵和圆形图案.
     ... nullsrc           |->V       Null video source, return unprocessed video frames.
                                      生成空视频源,返回未处理的空视频帧.
     ... rgbtestsrc        |->V       Generate RGB test pattern.
                                      生成 RGB 测试图案,横向红绿蓝三条图案.
     ... smptebars         |->V       Generate SMPTE color bars.
                                      生成 SMPTE 颜色条图案,像电视测试信号视频.
     ... smptehdbars       |->V       Generate SMPTE HD color bars.
                                      生成 SMPTE HD 颜色条图案.
     ... testsrc           |->V       Generate test pattern.
                                      生成测试图案.
     ... testsrc2          |->V       Generate another test pattern.
                                      生成另一个测试图案.
     ... nullsink          V->|       Do absolutely nothing with the input video.
                                      生成空视频模板,与输入视频无关.
     ... concat            N->N       Concatenate audio and video streams.
                                      连接音频和视频流.
     ... movie             |->N       Read from a movie source.
                                      从视频源读入视频.
     ... buffer            |->V       Buffer video frames, and make them accessible to the filterchain.
                                      缓冲视频帧,并用于滤镜链.
     ... buffersink        V->|       Buffer video frames, and make them available to the end of the filter graph.
                                      缓冲视频帧,并用于滤镜图的结束.
     ... fifo              V->V       Buffer input images and send them when they are requested.
                                      缓冲输入帧,若需要时.
```



# ffmpeg audio

SwrContext常用函数
1)swr_alloc

函数原型：struct SwrContext *swr_alloc(void);
此函数用于申请一个SwrContext结构体

    1
    2

2)swr_init

函数原型：int swr_init(struct SwrContext *s);
当设置好相关的参数后，使用此函数来初始化SwrContext结构体

    1
    2

3)swr_alloc_set_opts

函数原型：struct SwrContext *swr_alloc_set_opts(struct SwrContext *s,
                                      int64_t out_ch_layout, enum AVSampleFormat out_sample_fmt, int out_sample_rate,
                                      int64_t  in_ch_layout, enum AVSampleFormat  in_sample_fmt, int  in_sample_rate,
                                      int log_offset, void *log_ctx);

    1
    2
    3
    4

此函数是比较重要的函数，分配SwrContext并设置/重置常用的参数。
相关参数解释如下：

 * @param s               Swr context, can be NULL
 * @param out_ch_layout   output channel layout (AV_CH_LAYOUT_*)
 * @param out_sample_fmt  output sample format (AV_SAMPLE_FMT_*).
 * @param out_sample_rate output sample rate (frequency in Hz)
 * @param in_ch_layout    input channel layout (AV_CH_LAYOUT_*)
 * @param in_sample_fmt   input sample format (AV_SAMPLE_FMT_*).
 * @param in_sample_rate  input sample rate (frequency in Hz)
 * @param log_offset      logging level offset
 * @param log_ctx         parent logging context, can be NULL

    1
    2
    3
    4
    5
    6
    7
    8
    9

上面的参数即包含了输入输出参数中sample rate(采样率)、sample format(采样格式)、channel layout等参数。
4)swr_convert

函数原型：int swr_convert(struct SwrContext *s, uint8_t **out, int out_count,
                                const uint8_t **in , int in_count);

    1
    2

此函数便是将输入的音频按照定义的参数进行转换，并输出
5)swr_free

函数原型:void swr_free(struct SwrContext **s);
释放掉SwrContext结构体并将此结构体置为NULL;

    1
    2

三、基本用法

此结构体比较简单，参考FFMPEG中头文件 swresample.h中说明，基本用法如下：
申请结构体—>设置相关参数—>初始化—>转换—->释放结构体

申请结构体和设置相关参数有两种方法：
方法1：

 SwrContext *swr = swr_alloc();
 av_opt_set_channel_layout(swr, "in_channel_layout",  AV_CH_LAYOUT_5POINT1, 0);
 av_opt_set_channel_layout(swr, "out_channel_layout", AV_CH_LAYOUT_STEREO,  0);
 av_opt_set_int(swr, "in_sample_rate",     48000,                0);
 av_opt_set_int(swr, "out_sample_rate",    44100,                0);
 av_opt_set_sample_fmt(swr, "in_sample_fmt",  AV_SAMPLE_FMT_FLTP, 0);
 av_opt_set_sample_fmt(swr, "out_sample_fmt", AV_SAMPLE_FMT_S16,  0);

    1
    2
    3
    4
    5
    6
    7

方法2：

 SwrContext *swr = swr_alloc_set_opts(NULL,  // we're allocating a new context
                        AV_CH_LAYOUT_STEREO,  // out_ch_layout
                        AV_SAMPLE_FMT_S16,    // out_sample_fmt
                        44100,                // out_sample_rate
                        AV_CH_LAYOUT_5POINT1, // in_ch_layout
                        AV_SAMPLE_FMT_FLTP,   // in_sample_fmt
                        48000,                // in_sample_rate
                        0,                    // log_offset
                        NULL);                // log_ctx

# ffmpeg video



# ffmpeg 解码



# ffmpeg 编码

# ffmpeg mux



# ffmpeg源代码解析

AVStream AVCodecContext AVCodec

- 每个AVStream存储一个视频/音频流的相关数据；
- 每个AVStream对应一个AVCodecContext，存储该视频/音频流使用解码方式的相关数据；
- 每个AVCodecContext中对应一个AVCodec，包含该视频/音频对应的解码器。
- 每种解码器都对应一个AVCodec结构。



# frei0r

https://www.dyne.org/software/frei0r/