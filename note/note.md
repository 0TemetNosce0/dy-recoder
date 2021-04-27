

完成屏幕采集(DXGI)和H.264编码。

完成音频采集(WASAPI)和AAC编码。



屏幕采集: DXGI(win8以上), GDI

音频采集: WASAPI

编码器: [ffmpeg4.0](https://ffmpeg.org/), Version: 4.0

独显硬件编码器: [Video-Codec-SDK](https://developer.nvidia.com/nvidia-video-codec-sdk), Version: 8.2

核显硬件编码器: [Media-SDK](https://github.com/Intel-Media-SDK/MediaSDK)





# 参考

obs

https://github.com/daramkun/DaramCam

https://github.com/WindowsNT/ScreenCapture



# 音频输出捕获
core-audio-apis:https://docs.microsoft.com/zh-cn/windows/win32/coreaudio/core-audio-apis-in-windows-vista

在Windows操作系统上，常用的音频处理技术主要包括：Wave系列API函数、DirectSound、Core Audio。

其中，Core Audio只可以在Vista以上（包括Vista）的操作系统中才能使用，主要用来取代Wave系列API函数和DirectSound。

Core Audio实现的功能也比较强大，能实现对麦克风的采集、声卡输出的采集、控制声音的播放。

loopback模式

该方式就是我们需要实现的方式，即把扬声器里播放的声音抓取下来。

Windows下如何对声卡音频输出进行录音https://blog.csdn.net/qiuchangyong/article/details/104486716/

捕获输出
再看这个关于Loopback Recording的https://docs.microsoft.com/zh-cn/windows/win32/coreaudio/loopback-recording
```
 hr = _AudioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, AUDCLNT_STREAMFLAGS_EVENTCALLBACK | AUDCLNT_STREAMFLAGS_NOPERSIST, 20*10000, 0, _MixFormat, NULL);//AUDCLNT_STREAMFLAGS_EVENTCALLBACK使能事件触发.
```