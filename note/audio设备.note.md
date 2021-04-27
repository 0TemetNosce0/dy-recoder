# win 音频 Api

https://docs.microsoft.com/zh-cn/windows/win32/coreaudio/about-the-windows-core-audio-apis

# MMDevice API

https://docs.microsoft.com/zh-cn/windows/win32/coreaudio/mmdevice-api





# 相关类

```
IMMDevice 	表示音频设备。
IMMDeviceCollection 	表示音频设备的集合。
IMMDeviceEnumerator 	提供用于枚举音频设备的方法。
IMMEndpoint 	表示音频终结点设备。

IPropertyStore 属性表
IMMEndpoint //音频终结点设备

IAudioClient
IAudioRenderClient

WAVEFORMATEX

IMMNotificationClient
```

```cpp
IMMDeviceEnumerator //设备枚举,
IMMDeviceEnumerator::EnumAudioEndpoints 	//生成满足指定的音频设备集合,比如输入或输出设备集合,
IMMDeviceEnumerator::GetDefaultAudioEndpoint 	//获取默认设备
IMMDeviceEnumerator::GetDevice 	//通过id获取设备
IMMDeviceEnumerator::RegisterEndpointNotificationCallback //注册通知
IMMDeviceEnumerator::UnregisterEndpointNotificationCallback //取消通知
```

```//
IMMDeviceCollection //音频设备集合
IMMDeviceCollection::GetCount 	//获取设备集合中设备的个数
IMMDeviceCollection::Item //通过索引获取设备IMMDevice
```
```
IMMDevice 
//以下方法之一获取IMMDevice 
IMMDeviceCollection::Item
IMMDeviceEnumerator::GetDefaultAudioEndpoint
IMMDeviceEnumerator::GetDevice

//方法
IMMDevice::Activate 	//激活设备
IMMDevice::GetId 	//获取设备id
IMMDevice::GetState 	 //获取设备状态
IMMDevice::OpenPropertyStore 	//获取设备属性表IPropertyStore
```

```
IPropertyStore 属性表
IPropertyStore::Commit 	      //在进行更改之后，此方法保存更改。
IPropertyStore::GetAt        //获取属性键值key
IPropertyStore::GetCount 	//获取属性个数
IPropertyStore::GetValue 	//获取指定属性的值
IPropertyStore::SetValue 	//设置指定属性的值
```

```
IMMEndpoint //音频终结点设备  获取设备eRender和eCapture（通过IMMDevice查询获取）
IMMEndpoint::GetDataFlow //指示音频端点设备是渲染设备还是捕获设备。
```

```
 ERole 设备角色
设备可以有三个角色：控制台、通信和多媒体。下表描述了在 ERole 枚举中由三个常量（EConsole、ECommunications 和 eMultimedia）标识的设备角色。

```



```
IAudioClient  //声卡客户端接口,可获取声卡输出的音频参数、初始化声卡、获取声卡输出缓冲区的大小、开启/停止对声卡输出的采集

IAudioClient::GetBufferSize 	//缓冲区最多可以存放多少帧的数据量
IAudioClient::GetCurrentPadding 	//当前缓冲区中填充帧的数量
IAudioClient::GetDevicePeriod 	 //
IAudioClient::GetMixFormat 	//获取音频引擎用于内部处理共享模式流的流格式
IAudioClient::GetService 	///创建采集管理接口
IAudioClient::GetStreamLatency 	//获取当前流的最大延迟，可以在流初始化后的任何时间调用。
IAudioClient::Initialize 	////初始化管理对象，在这里，你可以指定它的最大缓冲区长度，这个很重要，应用程序控制数据块的大小以及延时长短都靠这里的初始化，具体参数大家看看文档解释,通过此方法，客户端指定流的数据格式、终结点缓冲区的大小，以及流是在共享模式还是独占模式下运行。
IAudioClient::IsFormatSupported 	//格式是否支持
IAudioClient::Reset 	
IAudioClient::SetEventHandle 	
IAudioClient::Start 	//开始音频流
IAudioClient::Stop 	//stop音频流
```
```
IAudioRenderClient  //声卡输出客户端接口
//可将采集的声音数据写入声音输出设备的缓存单元，输出设备可以通过IAudioClient::GetService函数获取 IAudioRenderClient 接口。

IAudioRenderClient::GetBuffer 	//获取下一个可用空间的指针，调用者可以向其中写入数据包。
IAudioRenderClient::ReleaseBuffer 	//释放在前面调用IAudioRenderClient::GetBuffer方法中获得的缓冲区空间。
```

```
 WAVEFORMATEX 
 
 typedef struct tWAVEFORMATEX {
  WORD  wFormatTag;//pcm格式是0, Adpcm是1.杜比Ac2是30 等等...
  WORD  nChannels;//通道数
  DWORD nSamplesPerSec;//采样率
  DWORD nAvgBytesPerSec;//平均传输速率。如果是PCM的话，则该值等于nSamplesPerSec除以nBlockAlign
  WORD  nBlockAlign;//数据块调整度(块对其,字节)，其值为通道数*样本的数据位值/8，
  WORD  wBitsPerSample;//每个样本的位数,表示每个声道中各个样本的数据位数,
  WORD  cbSize;//额外信息的大小，以字节为单位，额外信息添加在WAVEFORMATEX结构的结尾
} WAVEFORMATEX, *PWAVEFORMATEX, *NPWAVEFORMATEX, *LPWAVEFORMATEX;
```





# IMMNotificationClient

```
IMMNotificationClient 	当添加或删除音频终结点设备、设备的状态或属性更改时，或者在分配给设备的默认角色发生变化时，将提供通知。
```

# 音频设备的角色

windows的音频接口之前没接触过，今天先翻译一个简短的文章，介绍音频设备的角色（role）。原文链接：[Device Role](https://link.zhihu.com/?target=https%3A//docs.microsoft.com/en-us/windows/win32/coreaudio/device-roles)。

译文：

如果一个系统有两个或者多个音频渲染终端设备，其中一个设备或许最适合播放某种音频内容，另一个设备或许最适合播放另一种音频内容。比如，系统有两个音频渲染设备，用户或许会选择其中一个设备来播放音乐，选择另一个设备来播放系统通知声音。

相似地，如果一个系统有两个或者多个音频获取终端设备，其中一个设备或许最合适捕获某种音频内容，而另一个设备或许更适合捕获另一种音频内容。举个例子，如果一个系统有两个音频获取设备，用户可能会选取一个设备录制现场音乐，使用另一个来进行语音命令。

音频设备有三种角色，Console、Communications 和 Multimedia。下面的描述了被ERole 枚举中三个常量eConsole, eCommunications 和 eMultimedia定义的角色。

1. eConsole：负责和电脑进行交互，例如，在游戏和系统通知时会作为渲染设备，在语音命令时作为音频获取设备。
2. eCommunications：负责和其他人进行语音交流，例如，在聊天和语音通话时作为音频渲染和音频捕获设备。
3. eMultimedia： 负责播放或者录制音频声音，例如，在看电影或者听音乐的时候作为音频渲染设备，在记录解说或者现场音乐作为音频获取设备。

一个特定的音频获取或者渲染设备，可能会被标记为上面提到的三个角色中的一个、两个或者全部，甚至什么也不标记。任何时候，上面的三个角色只会被指定给一个（仅且一个）音频获取设备和一个（仅且一个）音频渲染设备。也就是说，对音频获取设备的角色绑定和对音频渲染设备的角色绑定相互独立，两者没什么关系。

一个应用可以通过单个音频渲染终端设备播放它的所有输出流，通过单个音频获取设备捕获所有的输入流。或者应用可以选择一部分输出流在某个音频渲染设备播放，剩下的输出流在另一个音频渲染设备播放。相似地，应用可以选择在一个音频捕获设备获取部分输入流，在另一个音频获取设备上获取其他输入流。也就是说，应用可以根据每个流的具体情况选择相应角色最合适的音频设备。

举个例子，网络语音应用可以将包含来电通知的输出流指定给角色为eConsole的音频输出设备。

ps：测试的时候HDMI设备角色会被赋值eCommunications，不知道为什么。

# 设备格式

https://docs.microsoft.com/zh-cn/windows/win32/coreaudio/device-formats







# 事件SetEvent、RestEvent、WaitForSingleObject与CreateEvent详解


SetEvent/ResetEvent分别将EVENT置为这两种状态分别是发信号与不发信号。

WaitForSingleObject()等待，直到参数所指定的OBJECT成为发信号状态时才返回，OBJECT可以是EVENT，也可以是其它内核对象。注：WaitForSingleObject的第一个参数一定不能为空。

CreateEvent 用来创建或打开一个命名的或无名的事件对象，对于它的其他解释，请自行百科，这里只简单描述它的两种常用用法！

CreateEvent 的定义如下：
```
HANDLE WINAPI CreateEvent(  
_In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes,                    //安全属性 
_In_     BOOL                  bManualReset,                         //设置信号复位方式为自动恢复为无信号状态(FALSE)还是手动恢复为无信号状态（TRUE） 
 _In_     BOOL                  bInitialState,                        //初始状态  
 _In_opt_ LPCTSTR               lpName                                //信号名称，可以为Null
）；
```
使用方法：
第一种情况 自动恢复到无信号状态
```
hEvent = CreateEvent(NULL, FALSE, TRUE, NULL); //复位方式为自动恢复到无信号状态，且初始状态为有信号.
DWORD dReturn = WaitForSingleObject(hEvent, 等待时间);  // 即调用完该方法后，hEvent 就变为无信号状态， 需要调用setEvent使其为有信号状态
```

hEvent 就会变为无信号状态，如果在某个时候再次需要上面的式子成立并通过，则需要使用下面的语句使其变为有信号状态（此方式只能解锁一个等待线程，如需继续解锁，则需要再次使用下面的式子）
```
SetEvent(hEvent)
```

第二种情况手动恢复到无信号状态
```
hEvent = CreateEvent(NULL, TRUE, TRUE, NULL); //复位方式为手动恢复到无信号状态，且初始状态为有信号.
DWORD dReturn = WaitForSingleObject(hEvent, 等待时间); //调用该方法后，事件会自动变为有信号
```

hEvent 就会自动再次变为有信号状态，上面的式子会直接执行并通过（同时有多个等待线程也会直接执行并通过），如果需要将hEvent设置为无信号状态，则需要手动使用下面的语句：
```
ResetEvent(hEvent);
```

注：上面的复位方式指的是恢复到无信号状态的方式，若设置为TRUE，则表示需要手动将其置为无信号，若为FALSE，则会自动变为无信号，千万别和信号量变为有信号状态的方式搞混了！
