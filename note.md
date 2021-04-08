# DXGI快速截屏录屏技术

很多地方都需要用到截屏/录屏技术，比如桌面直播，桌面录制等等。在微软Windows平台，有很多截屏的接口，不过大多数性能并不理想，Windows8以后微软引入了一套新的接口，叫“**Desktop Duplication API**”，应用程序，可以通过这套API访问桌面数据。而由于Desktop Duplication API是通过Microsoft DirectX Graphics Infrastructure (DXGI)来提供桌面图像的，速度非常快。由于是通过GPU，所以cpu占用率很低，性能很高。

  还有一点有意思的是，Duplication API获取到的桌面数据，不管显示模式如何设置，都永远是32位RGBA数据，其实这样方便的多了，不用考虑其他可能的情况，比如24位等。

  综合来看，各方面秒杀GDI截屏技术，易用性上也比MirrorDriver技术好得多，是Windows8以后平台的截屏技术首选。



d3d在

![https://img-blog.csdn.net/20161118172053864?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQv/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center](https://img-blog.csdn.net/20161118172053864?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQv/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

Desktop Duplication API此方法仅支持Win8及以上系统 截屏效率可达60fps/s 可以截取屏幕独占的游戏图像。

# ScreenCapture 使用dxgi

https://docs.microsoft.com/en-us/windows/win32/direct3ddxgi/desktop-dup-api

https://www.codeproject.com/Articles/5256890/ScreenCapture-Single-header-DirectX-library

首先，这套接口是集成在DirextX之中的，所以更大部分DirectX接口的使用方式基本一致，也就是通过D3D，各种QueryInterface，各种Enum，核心方法，是AcquireNextFrame。先简单说下流程。

    创建D3DDevice
    通过一系列接口获取路径，获取到IDXGIOutputDuplication接口
    调用AcquireNextFrame，获取当前桌面数据，保存在IDXGIResource中
    把数据从GPU映射到内存中
    拷贝需要的数据到自己的buffer里
————————————————
版权声明：本文为CSDN博主「haibindev」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/haibindev/article/details/84061641



# GDI捕获





# 参考

obs

https://github.com/daramkun/DaramCam

https://github.com/WindowsNT/ScreenCapture