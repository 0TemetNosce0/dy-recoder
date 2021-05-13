[TOC]

Surfaces
一个surface代表了显存中的一块线性区域，通常在显卡的显存中，尽管surface也可以存在系统内存中。surface是被IDirect3DSurface9接口管理的。

 1. front buffer：一块矩形内存，会被graphics　adapter翻译并在显示屏上显示。在Ｄ３Ｄ中，程序从来不会直接往front　buffer上写的。
 2. back buffer：一块矩形内存，程序可以直接写；它永远不会直接被显示到显示器上。
 3. flipping surface： 将back buffer移到front buffer的过程。
 4. swap chain： 一组，一个或多个，back buffer，可以被顺序地present到front buffer上。

一个IDXGISwapChain接口实现一个或多个Surface来存储呈现输出前的渲染数据。
IDXGISwapChain交换链封装2个以上的后背缓冲区用于渲染和显示。他们通常包含一个前置缓冲区用于显示和一个后背缓冲区用于渲染。实时上下文用于渲染后背缓冲区，交换链通过交换两个缓冲区来显示图像。


初始化Direct3D-11分为以下几个步骤

    描述交换链
    创建D3D设备
    创建设备上下文接口
    创建交换链接口
    创建目标渲染视图
    创建深度模板缓存视图(可选)
    设置视口
D3DX11CompileFromFile已弃用 换成D3DCompileFromFile

D3DX11SaveTextureToFile//DirectXTex库的接口

```cpp
HRESULT result = D3DX11SaveTextureToFile(
    g_pImmediateContext, tex, D3DX11_IFF_PNG, "name.png");
```

# DirectX graphics and gaming

https://docs.microsoft.com/en-us/windows/win32/directx

- [Direct3D](https://docs.microsoft.com/en-us/windows/win32/direct3d)
- [Direct2D](https://docs.microsoft.com/en-us/windows/win32/direct2d/direct2d-portal)
- [DXCore](https://docs.microsoft.com/en-us/windows/win32/dxcore/dxcore)
- [DirectXMath](https://docs.microsoft.com/en-us/windows/win32/dxmath/directxmath-portal)
- [XAudio2 APIs](https://docs.microsoft.com/en-us/windows/win32/xaudio2/xaudio2-apis-portal)

  examples: https://github.com/microsoft/DirectX-Graphics-Samples



# DirectXMath

从Windows8开始，DirectX 11中xnamath.h就去掉了，替换成DirectXMath.h头文件。所以如果遇到一些在旧系统上开发的代码示例，如果提示找不到xnamath.h的话，可以先简单按照下面方法处理：


#include <xnamath.h>

变成：

#include <DirectXMath.h>
using namespace DirectX;

或者不用using namespace， 在程序里添加前缀调用，例如：

DirectX::XMFLOAT3 position;

# direct3d

https://docs.microsoft.com/en-us/windows/win32/direct3d

https://docs.microsoft.com/en-us/windows/win32/direct3d11/atoc-dx-graphics-direct3d-11
Swapchain

Swapchain用来交换前后台缓冲之间的数据。这个技术也叫做双缓存技术。当我们渲染场景的时候，一般我们都是把它渲染到后台缓冲中，当我们把后台缓冲展示到屏幕上的时候，它已经被渲染好了。否则的话，我们就会在屏幕上看到一个扫描线（这是光栅化阶段，对屏幕进行填充颜色，之后的章节会讲到）
2.代表GPU硬件设备的接口

而DitectX11把D3d11Device接口一分为二，这样可以支持多线程。

1.ID3D11DeviceContext接口（用来处理和调用渲染相关的函数）

2.ID3D11Device（用来处理调用和渲染无关的函数）

一分为二的原因：当我们在加载一个模型或者创建一个物体的时候，我们可以调用ID3D11Device对象，这个时候，我们可以同时调用ID3D11DeviceContext对象来对我们的场景进行渲染。
3.render target view

上文已经提到过了，我们需要先渲染到后台缓存，接着再把后台缓存的数据渲染到屏幕上。

render target view就是我们的后台缓存，本质上是个2d的纹理图。之后会被渲染管线中的其它部分调用，最终渲染到屏幕上。

# DirectX11 基本初始化流程

代码部分参考：

《Beginning.DirectX.11.Game.Programming》第二章


流程图:

 


文字描述：

1、创建设备、设备上下文和交换链接（调用核心函数CreateDeviceAndSwapChain）

2、通过GetBuffer获取后台缓存，判断是否能够获取后台缓存。

3、使用Direct设备创建一个要渲染的目标视窗

4、通过设备上下文获取当前的渲染目标视窗指针，并将这个指针放置到之前创建的目标视窗中。

5、先创建一个ViewPort，然后设定对应的值。在设备上下文中设置这个ViewPort

6、在设备上下文中使用之前创建的目标视窗，设定好颜色后使用ClearRenderTargetView填充后台视窗缓存

7、将后台缓存呈现给用户
————————————————
版权声明：本文为CSDN博主「sagakiss」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/sagakiss/article/details/8373948

## ID3D11Device   ID3D11DeviceContext    IDXGISwapChain

```
   DXGI_SWAP_CHAIN_DESC sd;//描述
    ZeroMemory( &sd, sizeof( sd ) );
    sd.BufferCount = 1;
    sd.BufferDesc.Width = 640;
    sd.BufferDesc.Height = 480;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = g_hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    
    D3D_FEATURE_LEVEL FeatureLevels = D3D_FEATURE_LEVEL_11_0;
     
    HRESULT hr = S_OK;
    ID3D11Device           *d3d11_device;//设备
    ID3D11DeviceContext    *d3d11_context;//设备上下文
    IDXGISwapChain         *dxgi_swap;//交换链 ,用于渲染
    D3D_FEATURE_LEVEL FeatureLevel;
    if( FAILED (hr = D3D11CreateDeviceAndSwapChain( NULL, //NULL使用默认的适配器
                    D3D_DRIVER_TYPE_REFERENCE, //驱动类型
                    NULL, 
                    0,
                    &FeatureLevels, 
                    1, 
                    D3D11_SDK_VERSION, 
                    &sd, 
                    &dxgi_swap, 
                    &d3d11_device, 
                    &FeatureLevel,
                    &d3d11_context )))
    {
        return hr;
    }
```
D3D11CreateDeviceAndSwapChain函数
```
HRESULT  D3D11CreateDeviceAndSwapChain(
__in   IDXGIAdapter *pAdapter,
__in   D3D_DRIVER_TYPE DriverType,
__in   HMODULE Software,
__in   UINT Flags,
__in   const D3D_FEATURE_LEVEL *pFeatureLevels,
__in   UINT FeatureLevels,
__in   UINT SDKVersion,
__in   const DXGI_SWAP_CHAIN_DESC *pSwapChainDesc,
__out  IDXGISwapChain **ppSwapChain,
__out  ID3D11Device **ppDevice,
__out  D3D_FEATURE_LEVEL *pFeatureLevel,
__out  ID3D11DeviceContext **ppImmediateContext
);

/////
参数：
pAdapter[in]
IDXGIAdapter
该显卡指针用于适配器创建过程。通过NULL使用默认的适配器，该适配器来至
IDXGIFactory1::EnumAdapters枚举中的第一项。
     注意不要在一个应用程序中混合使用 DXGI 1.0（IDXGIFactory）和DXGI 1.1（IDXGIFactory1）。使用
       IDXGIFactory或IDXGIFactory1，但不要两者在一个程序中使用。

DriverType[in]
D3D_DRIVER_TYPE
D3D_DRIVER_TYPE代表创建时的驱动类型。

 
Software[in]
HMODULE
DLL中的一个软件光栅句柄。如果DriverType设置为D3D_DRIVER_TYPE_SOFTWARE时Software不能为NULL
通过LoadLibrary，LoadLibraryEx，或GetModuleHandle来获取这个句柄。当D3D_DRIVER_TYPE值为
D3D_DRIVER_TYPE_SOFTWARE时，这个值必须不为NULL，否则无效。

 
Flags[in]
UINT
该参数用于运行层（参考D3D_CREATE_DEVICE_FLAG）;该值可以进行位的与或操作。

 
pFreatureLevels[in]
D3D_FEATURE_LEVEL
这个指针指向一个D3D_FEATURE_LEVEL数组，来决定创建时排序的功能级别。默认使用最佳的功能级别。
如果pFeatureLevels为NULL，将使用以下的功能级别：

    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };


FeatureLevels[in]
UINT
pFeatureLevels中的元素数量.

 SDKVersion[in]
UINT
SDK版本；使用D3D11_SDK_VERSION

 
pSwapChainDesc[in]
DXGI_SWAP_CHAIN_DESC
这个指针指向一个交换链接描述（参考：DXGI_SWAP_CHAIN_DESC），包含用于这个交换链接的初始化参数

 
ppSwapChain[out]
IDXGISwapChain
返回一个IDXGISwapChain对象的指针地址，这个交换链接用于渲染。

 
ppDevice[out]
ID3D11Device
返回一个创建好的 ID3D11Device对象的指针地址。供应一个NULL指针，返回一个pFeatureLevel中所支持的
最高功能级别。

 
pFeatureLevel[out]
D3D_FEATURE_LEVEL
返回一个D3D_FEATURE_LEVEL指针，它来着pFeatureLevel中设备所支持的第一个元素。

 
ppImmediateContext[out]
ID3D11DeviceContext
返回一个ID3D11DeviceContext对象指针，它代表这个设备上下文。

 
返回值
HRESULT
这个函数返回Direct3D 11返回值。 
```



D3D_DRIVER_TYPE枚举

```
typedef enum D3D_DRIVER_TYPE {
  D3D_DRIVER_TYPE_UNKNOWN     = 0,
  D3D_DRIVER_TYPE_HARDWARE    = ( D3D_DRIVER_TYPE_UNKNOWN + 1 ),
  D3D_DRIVER_TYPE_REFERENCE   = ( D3D_DRIVER_TYPE_HARDWARE + 1 ),
  D3D_DRIVER_TYPE_NULL        = ( D3D_DRIVER_TYPE_REFERENCE + 1 ),
  D3D_DRIVER_TYPE_SOFTWARE    = ( D3D_DRIVER_TYPE_NULL + 1 ),
  D3D_DRIVER_TYPE_WARP        = ( D3D_DRIVER_TYPE_SOFTWARE + 1 ) 
} D3D_DRIVER_TYPE;
//////
D3D_DRIVER_TYPE_UNKNOWN
驱动类型未知

D3D_DRIVER_TYPE_HARDWARE
硬件驱动，硬件支持所有Direct3D功能。

D3D_DRIVER_TYPE_REFERENCE   参考类型驱动，通过软件来支持所有的Direct3D功能。

D3D_DRIVER_TYPE_NULL
NULL驱动，这是一个参考驱动，不渲染任何内容。

D3D_DRIVER_TYPE_SOFTWARE
软件驱动，这个驱动所有功能有软件实现。

D3D_DRIVER_TYPE_WARP
 WARP驱动，这个是一个搞性能的软件光栅。这个软件光栅支持9_1到10.1的功能级别。
```
D3D_FEATURE_LEVEL枚举
设置一个Direct3D 设备的功能级别目标。
```
typedef enum D3D_FEATURE_LEVEL {
  D3D_FEATURE_LEVEL_9_1    = 0x9100,
  D3D_FEATURE_LEVEL_9_2    = 0x9200,
  D3D_FEATURE_LEVEL_9_3    = 0x9300,
  D3D_FEATURE_LEVEL_10_0   = 0xa000,
  D3D_FEATURE_LEVEL_10_1   = 0xa100,
  D3D_FEATURE_LEVEL_11_0   = 0xb000 
} D3D_FEATURE_LEVEL;
//////////
D3D_FEATURE_LEVEL_9_1 

目标功能级别支持Direct3D 9.1包含 shader model 2.


D3D_FEATURE_LEVEL_9_2

目标功能级别支持Direct3D 9.2包含 shader model 2.


D3D_FEATURE_LEVEL_9_3   目标功能级别支持Direct3D 9.3包含 shader model 3.


D3D_FEATURE_LEVEL_10_0

目标功能级别支持Direct3D 10.0包含 shader model 4.


D3D_FEATURE_LEVEL_10_1

目标功能级别支持Direct3D 10.1包含 shader model 4.


D3D_FEATURE_LEVEL_11_0

目标功能级别支持Direct3D 11.0包含 shader model 5.

```
DXGI_SWAP_CHAIN_DESC结构体
描述一个交换链接。
```
typedef struct DXGI_SWAP_CHAIN_DESC {
  DXGI_MODE_DESC   BufferDesc;
  DXGI_SAMPLE_DESC SampleDesc;
  DXGI_USAGE       BufferUsage;
  UINT             BufferCount;
  HWND             OutputWindow;
  BOOL             Windowed;
  DXGI_SWAP_EFFECT SwapEffect;
  UINT             Flags;
} DXGI_SWAP_CHAIN_DESC;
/////
 BufferDesc
DXGI_MODE_DESC
一个DXGI_MODE_DESC结构体，用来描述后台缓存显示模式。

SampleDesc
DXGI_SAMPLE_DESC
一个DXGI_SAMPLE_DEC结构体，用来描述多次采样参数。

BufferUsage
DXGI_USAGE
一个DXGI_USAGE枚举类型描述后台缓存的表面用法和CPU访问设置。后台缓存能使用渲染输入或渲染目标输出

BufferCount
UINT
这个值用于描述交换链接的缓存数量，包含前置缓存。

OutputWindow
HWND
用于输出Window的一个HWND句柄。这个成员必须不是NULL.

Windowed
BOOL
如果值为true将会已窗口模式显示；全屏则为false;

SwapEffect
DXGI_SWAP_EFFECT
这是一个DXGI_SWAP_EFFECT枚举类型，描述处理目前的缓存和目前的表面的设置。

Flags
UINT
这个成员是一个 DXGI_SWAP_EFFECT枚举类型，描述交换链接行为设置。 
```

DXGI_MODE_DESC结构体，其成分如下

    typedef struct DXGI_MODE_DESC
    {
        UINT Width;
        UINT Height;
        DXGI_RATIONAL RefreshRate;
        DXGI_FORMAT Format;
        DXGI_MODE_SCANLINE_ORDER ScanlineOrdering;
        DXGI_MODE_SCALING Scaling;
    } DXGI_MODE_DESC;
    
    UINT Width:描述窗口分辨率宽度。
    UINT Height:描述窗口分辨率高度。
    DXGI_RATIONAL RefreshRate:用于描述刷新频率的结构体。
    DXGI_FORMAT Format:用于描述显示格式的枚举类型。设置为DXGI_FORMAT_R8G8B8A8_UNORM即可
    DXGI_MODE_SCANLINE_ORDER ScanlineOrdering:用于描述扫描线绘制模式的枚举。可以设置为0
    DXGI_ODE_SCALING Scaling:用于描述缩放形式的枚举类型，默认使用DXGI_MODE_SCALING_UNSPECIFIED。

DXGI_RATIONAL结构体。成分如下

    typedef struct DXGI_RATIONAL
    {
        UINT Numerator;
        UINT Denominator;
    } DXGI_RATIONAL;
    
    UINT 类型的Numerator:表示刷新频率的分子
    UINT 类型的Denominator:表示刷新频率的分母
    Numerator=60,Denominator=1表示每秒刷新6次


DXGI_SAMPLE_DESC。



    typedef struct DXGI_SAMPLE_DESC
    {
        UINT Count;
        UINT Quality;
    } DXGI_SAMPLE_DESC;
    
    UINT类型的Count:描述每一个像素多重采样的次数。
    UINT类型的Quality:描述图像品质等级。有效范围是0~1，小于CheckMultisampleQualityLevels的返回值。
    默认值为Count=1,Quality=0;


ID3D11Device接口

```
ID3D11Device Interface
这个设备接口是一个虚拟适配器；它被用于运行渲染和创建资源。

成员
这个ID3D11Device接口继承至IUnknown接口。ID3D11Device定义了以下成员：

函数	描述
CheckCounter	获取类型、名称、计量单位，并说明现有的计数器。
CheckCounterInfo	获取一个计数器信息。
CheckFeatureSupport	获取当前显卡的功能支持信息。
ChecjMultisampleQualityLevels	获取多重采样的质量级别。
CheckFormatSupport	检查视频设备所支持的格式
CreateBlendState	创建一个blend-state对象，这个混合状态用于output-merger阶段
CreateBuffer	创建一个缓存（顶点缓存、索引缓存、着色器常量缓存）
CreateClassLinkage	创建一个类连接库能够动态连接着色器。
CreateComputeShader	创建一个计算着色器
CreateDeferredContext	创建一个延迟上下文播放命令列表
CreateCounter	创建一个计数器对象用于测量GPU性能。
CreateDepthStencilState	创建深度模板对象其包含深度模板测试信息用于output-merger阶段
CreateDepthStencilView	创建深度模板视图用于访问数据资源
CreateDomainShader	创建一个Domain着色器
CreateCeometryShader	创建网格着色器
CreateGeometryShaderWithStreamOuput	创建一个能够写入输出缓存流的网格着色器。
CreateHullShader	创建Hull着色器
CreateInputLayout	创建一个input-layout对象描述这个输入缓存数据用于input-assembler阶段
CreatePixelShader	创建一个像素着色器
CreatePredicate	创建一个断言
CreateQuery	这个是一个从GPU查询信息的包装函数
CreateRasterizerState	 创建一个光栅状态对象告诉光栅阶段如何执行
CreateReanderTargetView	创建一个渲染目标视图用于访问数据资源
CreateSamplerState	创建一个采样状态对象包含一个材质的采样信息。
CreateShaderResourceView	创建一个着色器资源视图，用于访问资源中的数据。
CreateTexture1D	创建一个1D材质数组
CreateTexture2D	创建一个2D材质数组
CreateTexture3D	创建一个3D材质
CreateUnorderedAccessView	创建一个视图来无序访问资源
CreateVertexShader	从编译着色器创建一个顶点着色器
GetCreationFlags	通过调用创建设备的D3D11CreateDevice获取这个标志
GetDeviceRemoveReason	获取设备被移除的原因
GetExceptionMode	获取异常模式标志
GetFeatureLevel	获取硬件设备的功能级别
GetImmediateContext	获取及时上下文，能够记录命令列表。
GetPrivateData	从子设备获取应用程序定义数据。
OpenSharedResource	提供一个访问共享资源，它由不同的设备创建
SetExceptionMode	设置异常模式标志
SetPrivateData	设置数据到一个设备的GUID关联的数据。
SetPrivateDataInterface	这个设备子对象关联的IUnknown派生的接口，该接口相关联的应用程序定义的GUID。

```

ID3D11DeviceContext接口

```

这个ID3D11DeviceContext接口实现一个设备上下文生成渲染命令。

ID3D11DeviceContext接口实现ID3D11DeviceChild.ID3D11DeviceContext也定义了一下成员函数：

成员	描述
Begin	标记开始的一系列命令。
ClearDepthStencilView	清除这个深度目标资源
ClearRenderTargetView	设置渲染目标的所有元素到一个值
ClearState	重置为所有默认设置
ClearUnordereAccessViewFloat	通过一个单精度值清除一个无序资源
ClearUnordereAccessViewUint	通过一个bit-precise值来清除一个无序资源
CopyResource	使用GPU拷贝所有的源资源到目标资源。
CopyStructureCount	从缓存中拷贝一个数据，包含可变长度数据。
CopySubresourceRegion	复制一个区域从原资源到目标资源。
CSGetConstantBuffers	获取缓存常量使用在计算着色器阶段。
CSGetSamplers	获取采样状态接口数组来自计算着色器阶段。
CSGetShader	从当前设置的设备的计算着色器。
CSGetShaderResources	获取计算着色器资源。
CSGetUnorderedAccessViews	从一个无序资源中获取一个视图数组。
CSSetConstantBuffers	在计算着色器阶段设置缓存常量
CSSetSamplers	在计算着色器阶段设置一个采样状态数组
CSSetShader	为设备设置一个计算着色器
CSSetShaderResoures	在计算着色器阶段绑定一个着色器资源数组中
CSSetUnorderedAccessViews	为一个无序资源设置一个视窗数组
Dispatch	从一个线程组执行一个命令列表
DispatchIndirect	在一个多线程组中执行一个命令行列表绘制GPU-generated图元
Draw	绘制非引索，非实例化图元
DrawAuto	绘制一个未知大小的网格
DrawIndexed	绘制一个引索、非实例化图元
DrawIndexInstanced	绘制一个殷素素的、实例化的GPU-generated图元
DrawInstance	绘制一个没有引索的实例化图元
DrawInstancedIndirect	绘制一个实例化的GPU-generated图元
DSGetConstantBuffers	在domain-shader阶段获取一个缓存常量
DSGetSamplers	从domain-shader阶段获取采样状态数组
DSGetShaderResources	获取domain-shader资源
DSSetConstantBuffers	设置domain-shader阶段的缓存常量
DSSetShader	为设备设置一个domain shader
DSSetShaderResources	为domain-shader阶段绑定一个着色器资源数组
End	标记结束一系列命令
ExecuteCommandList	队列命令从命令列表中发送至设备
FinishCommandList	创建一个命令列表并记录图形命令
Flush	发送在命令缓冲区中排列好的命令到GPU
GenerateMips	为给予着色器资源生成mipmap贴图
GetContextFlags	获取初始化标志与当前环境延迟上下文
GetData	异步模式从GPU获取数据。
GetPredication	获取渲染断言状态。
GetResourceMinLOD	获取最小细节级别（LOD）
GetType	获取设备上下文类型

GSGetConstantBuffers
	获取网格着色器管线阶段所使用的常量缓存。
GSGetSamplers	获取来自网格着色器管线阶段的采样状态接口数组。
GSGetShader	获取这个设备的网格着色器当前设置。
GSGetShaderResources	获取网格着色器资源。
GSSetConstantBuffers	设置网格着色器管线阶段所使用的常量缓存。
GSSetSamplers	设置网格着色器管线阶段所使用的采样状态数组。
GSSetShader	为这个设备设置一个网格着色器
GSSetShaderResources	绑定一个着色器资源到网格着色器阶段。
HSGetConstantBuffers	获取用于hull-shader阶段的常量缓存
HSGetSamplers	从hull-shader阶段获取一个采样状态接口数组
HSGetShader	从设备获取当前设置的hull shader
HSGetShaderResources	获取hull shader资源
HSSetConstantBuffers	设置hull-shader阶段使用的常量缓存
HSSetSamplers	为hull-shader阶段设置一个采样状态数组。
HSSetShaderResources	为hull-shader阶段绑定一个着色器资源。
HSSetShader	为这个设备设置hull shader
IAGetIndexBuffer	获取一个索引缓冲区指针，一定在input-assembler阶段
IAGetInputLayout	在input-assembler阶段获取一个指向input-layout的指针。
IAGetPrimitiveTopology	获取图元类型的信息和数据顺序，描述了input-layout阶段的输入数据。
IAGetVertexBuffers	获取input-assembler阶段的顶点缓存
IASetIndexBuffers	绑定一个索引缓存到input-assembler阶段
IASetInputLayout	绑定一个input-layout对象到input-assembler阶段
IASetPrimitiveTopology	绑定图元类型信息和数据顺序，这些数据输入input-layout阶段
IASetVertexBuffers	绑定一个顶点缓存数组到input-layout阶段。
Map	获取一个包含子资源的指针数据，并且拒绝GPU访问这些子资源。
OMGetBlendStae	获取output-merger阶段的混合状态
OMGetDepthStencilState	获取output-merger阶段的深度模板状态
OMGetRenderTargets	获取output-merger阶段绑定的资源指针。
OMGetRenderTargetsAndUnorderedAccessViews	获取output-merger阶段绑定的资源指针。
OMSetBlendState	设置output-merger阶段的混合状态
OMSetDepthStencilState	设置output-merger阶段的深度模板状态
OMSetRenderTargets	绑定一个或多个渲染原子目标和深度模板缓存到output-merger阶段。
OMSetRenderTargetsAndUnorderedAccessViews	绑定资源到output-merger阶段
PSGetConstantBuffers	获取用于像素着色器管线阶段的常量缓存。
PSGetSamplers	获取像素着色器管线阶段所设定的采样状态数组
PSGetShader	获取当前设置所设定的像素着色器
PSGetShaderResources	获取像素着色器资源。
PSSetConstantBuffers	设定像素着色器管线状态的常量缓存。
PSSetSamplers	设定一个采样状态数组到像素着色器管线。
PSSetShaderResources	绑定一个着色器资源数组到像素着色器管线状态。
ResolveSubresource	拷贝一个多层采样资源到一个非多层采样资源中。
RSGetScissorRects	获取一个裁剪矩型数组到光栅阶段
RSGetState	从光栅阶段获取光栅状态
RSGetViewports	从光栅阶段获取其绑定的视口数组。
RSSetScissorRects	绑定一个裁剪矩形数组到光栅阶段管线
RSSetState	为光栅阶段管线设置光栅状态
RSSetViewports	绑定一个视口数组到光栅阶段管线
SetPredication	设定渲染断言
SetResourceMinLOD	设置一个资源的最小细节资源级别
SOGetTargets	获取stream-output 阶段的管线的目标的目标输出缓存
SOSetTargets	设置stream-output阶段的目标输出缓存
Unmap	使指向资源的指针无效，并让GPU's可访问这个资源
UpdateSubersource	这个CPU从内存拷贝数据到子资源，创建在不可变化内存。
VSGetConstantBUffers	从顶点着色器管线阶段获取常量缓存。
VSGetSamplers	从顶点着色器管线阶段获取一个采样数组。
VSGetShader	获取当前设备所设定的顶点着色器。
VSGetShaderResources	获取使用顶点着色器资源。
VSSetConstantBuffers	设定顶点着色器管线阶段所使用常量缓存
VSSetSamplers	设定顶点着色器管线阶段所使用的采样状态数组
VSSetShader	设定设备的顶点着色器
VSSetShaderResources	绑定一个着色器资源数组到顶点着色器阶段
```

IDXGISwapChain接口

```

一个IDXGISwapChain接口实现一个或多个Surface来存储呈现输出前的渲染数据。

 
成员
IDXGISwapChain接口继承于IDXGIDeviceSubObject.

GetBuffer	
访问交换链接的一个后台缓存。

GetContainingOutput
获取这个输出设备（当前显示器）所包含目标窗口的主要客户端区域。

GetDesc
获取交换链接描述。

GetFrameStatistics
获取最后渲染帧的性能统计。

GetFullscreenState
获取关于全屏模式的状态。

GetLastPresentCount
获取IDXGISwapChain::Present被调用的次数。

Present
呈现一个渲染图片给用户。

ResizeBuffers
修改交换链接后台缓存大小、格式、数目。这个函数需要在窗口大小变化后调用。

ResizeTarget
大小变化后的输出目标

SetFullscreenState
设置显示模式是全屏还是窗口


注意
有两种方法创建IDXGIFactory::CreateSwapChain或D3D11CreateDeviceAndSwapChain
```



枚举适配器



```
std::vector <IDXGIAdapter*> EnumerateAdapters(void)
{
    IDXGIAdapter * pAdapter; 
    std::vector <IDXGIAdapter*> vAdapters; 
    IDXGIFactory* pFactory = NULL; 
    

    // Create a DXGIFactory object.
    if(FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory) ,(void**)&pFactory)))
    {
        return vAdapters;
    }


    for ( UINT i = 0;
          pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND;
          ++i )
    {
        vAdapters.push_back(pAdapter); 
    } 


    if(pFactory)
    {
        pFactory->Release();
    }

    return vAdapters;

}
```
获取显示设备信息：
```
/************************************************************************
	FileName:main.cpp
	Descript:获取显卡信息
	Author:绝望的老猫
	Date:2012/12/23
************************************************************************/
 
#include <Windows.h>
#include <iostream>
#include <DXGI.h>
#include <vector>
 
using namespace std;
 
int main()
{
	// 参数定义
	IDXGIFactory * pFactory;
	IDXGIAdapter * pAdapter;	
	std::vector <IDXGIAdapter*> vAdapters;			// 显卡
	
 
	// 显卡的数量
	int iAdapterNum = 0;			
 
 
	// 创建一个DXGI工厂
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory) );
 
	if (FAILED(hr))
		return -1;
	
	// 枚举适配器
	while(pFactory->EnumAdapters(iAdapterNum, &pAdapter) != DXGI_ERROR_NOT_FOUND) 
	{ 
		vAdapters.push_back(pAdapter); 
		++iAdapterNum; 
	} 
 
	// 信息输出 
	cout<<"===============获取到"<<iAdapterNum<<"块显卡==============="<<endl;
	for (size_t i=0;i<vAdapters.size(); i++)
	{
		// 获取信息
		DXGI_ADAPTER_DESC adapterDesc;
		vAdapters[i]->GetDesc(&adapterDesc);
 
		// 输出显卡信息
		cout<<"系统视频内存:"<<adapterDesc.DedicatedSystemMemory/1024/1024<<"M"<<endl;
		cout<<"专用视频内存:"<<adapterDesc.DedicatedVideoMemory/1024/1024<<"M"<<endl;
		cout<<"共享系统内存:"<<adapterDesc.SharedSystemMemory/1024/1024<<"M"<<endl;
		cout<<"设备描述:"<<adapterDesc.Description<<endl;
		cout<<"设备ID:"<<adapterDesc.DeviceId<<endl;
		cout<<"PCI ID修正版本:"<<adapterDesc.Revision<<endl;
		cout<<"子系统PIC ID:"<<adapterDesc.SubSysId<<endl;
		cout<<"厂商编号:"<<adapterDesc.VendorId<<endl;
 
		// 输出设备
		IDXGIOutput * pOutput;
		std::vector<IDXGIOutput*> vOutputs;
		// 输出设备数量
		int iOutputNum = 0;
		while(vAdapters[i]->EnumOutputs(iOutputNum,&pOutput)!= DXGI_ERROR_NOT_FOUND)
		{
			vOutputs.push_back(pOutput);
			iOutputNum++;
		}
 
		cout<<"-----------------------------------------"<<endl;
		cout<<"获取到"<<iOutputNum<<"个显示设备:"<<endl;
		cout<<endl;
 
		for (size_t n=0;n<vOutputs.size();n++)
		{
			// 获取显示设备信息
			DXGI_OUTPUT_DESC outputDesc;
			vOutputs[n]->GetDesc(&outputDesc);
 
			// 获取设备支持
			UINT uModeNum = 0;
			DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;
			UINT flags         = DXGI_ENUM_MODES_INTERLACED;
 
			vOutputs[n]->GetDisplayModeList( format, flags, &uModeNum, 0);
			DXGI_MODE_DESC * pModeDescs = new DXGI_MODE_DESC[uModeNum];
			vOutputs[n]->GetDisplayModeList( format, flags, &uModeNum, pModeDescs);
 
			cout<<"显示设备名称:"<<outputDesc.DeviceName<<endl;
			cout<<"显示设备当前分辨率:"<<outputDesc.DesktopCoordinates.right-outputDesc.DesktopCoordinates.left <<"*"<<outputDesc.DesktopCoordinates.bottom-outputDesc.DesktopCoordinates.top<<endl;
			cout<<endl;
 
			// 所支持的分辨率信息
			cout<<"分辨率信息:"<<endl;
			for (UINT m=0;m<uModeNum;m++)
			{
				cout<<"== 分辨率:"<<pModeDescs[m].Width<<"*"<<pModeDescs[m].Height<<"     刷新率"<<(pModeDescs[m].RefreshRate.Numerator)/(pModeDescs[m].RefreshRate.Denominator)<<endl;
			}			
		}
		vOutputs.clear();
		
	}
	vAdapters.clear();
 
	system("pause");
	return 0;
}

```
## dxgi

https://docs.microsoft.com/en-us/windows/win32/direct3ddxgi/dx-graphics-dxgi

DXGI处理枚举图形适配器，枚举显示模式，选择缓冲格式，共享进程之间的资源，并呈现帧到窗口或显示器显示。

## High-level shader language (HLSL)

https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl

# D3D12 HDR

https://github.com/microsoft/DirectX-Graphics-Samples/tree/master/Samples/Desktop/D3D12HDR

# Multiple Display Monitors

https://docs.microsoft.com/en-us/windows/win32/gdi/multiple-display-monitors-functions

https://docs.microsoft.com/en-us/windows/win32/gdi/multiple-display-monitors-structures

| [**EnumDisplayMonitors**](https://docs.microsoft.com/en-us/windows/desktop/api/Winuser/nf-winuser-enumdisplaymonitors) | Enumerates display monitors that intersect a region formed by the  intersection of a specified clipping rectangle and the visible region of a device context. |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [**GetMonitorInfo**](https://docs.microsoft.com/en-us/windows/desktop/api/Winuser/nf-winuser-getmonitorinfoa) | Retrieves information about a display monitor.               |
| [**MonitorEnumProc**](https://docs.microsoft.com/en-us/windows/desktop/api/Winuser/nc-winuser-monitorenumproc) | An application-defined callback function that is called by the [**EnumDisplayMonitors**](https://docs.microsoft.com/en-us/windows/desktop/api/Winuser/nf-winuser-enumdisplaymonitors) function. |
| [**MonitorFromPoint**](https://docs.microsoft.com/en-us/windows/desktop/api/Winuser/nf-winuser-monitorfrompoint) | Retrieves a handle to the display monitor that contains a specified point. |
| [**MonitorFromRect**](https://docs.microsoft.com/en-us/windows/desktop/api/Winuser/nf-winuser-monitorfromrect) | Retrieves a handle to the display monitor that has the largest area of intersection with a specified rectangle. |
| [**MonitorFromWindow**](https://docs.microsoft.com/en-us/windows/desktop/api/Winuser/nf-winuser-monitorfromwindow) | Retrieves a handle to the display monitor that has the largest area  of intersection with the bounding rectangle of a specified window. |

# [HLSL编译着色器的三种方法](https://www.cnblogs.com/X-Jun/p/10066282.html)
[Compiling Shaders](https://docs.microsoft.com/zh-cn/windows/desktop/direct3dhlsl/dx-graphics-hlsl-part1#compiling-with-d3dcompilefromfile)

[How To: Compile a Shader](https://docs.microsoft.com/zh-cn/windows/desktop/direct3d11/how-to--compile-a-shader)



CreateShaderFromFile

```
// 安全COM组件释放宏
#define SAFE_RELEASE(p) { if ((p)) { (p)->Release(); (p) = nullptr; } }

// ------------------------------
// CreateShaderFromFile函数
// ------------------------------
// [In]csoFileNameInOut 编译好的着色器二进制文件(.cso)，若有指定则优先寻找该文件并读取
// [In]hlslFileName     着色器代码，若未找到着色器二进制文件则编译着色器代码
// [In]entryPoint       入口点(指定开始的函数)
// [In]shaderModel      着色器模型，格式为"*s_5_0"，*可以为c,d,g,h,p,v之一
// [Out]ppBlobOut       输出着色器二进制信息
HRESULT CreateShaderFromFile(const WCHAR * csoFileNameInOut, const WCHAR * hlslFileName,
    LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob ** ppBlobOut)
{
    HRESULT hr = S_OK;

    // 寻找是否有已经编译好的顶点着色器
    if (csoFileNameInOut && D3DReadFileToBlob(csoFileNameInOut, ppBlobOut) == S_OK)
    {
        return hr;
    }
    else
    {
        DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
        // 设置 D3DCOMPILE_DEBUG 标志用于获取着色器调试信息。该标志可以提升调试体验，
        // 但仍然允许着色器进行优化操作
        dwShaderFlags |= D3DCOMPILE_DEBUG;

        // 在Debug环境下禁用优化以避免出现一些不合理的情况
        dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
        ID3DBlob* errorBlob = nullptr;
        hr = D3DCompileFromFile(hlslFileName, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel,
            dwShaderFlags, 0, ppBlobOut, &errorBlob);
        if (FAILED(hr))
        {
            if (errorBlob != nullptr)
            {
                OutputDebugStringA(reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
            }
            SAFE_RELEASE(errorBlob);
            return hr;
        }

        // 若指定了输出文件名，则将着色器二进制信息输出
        if (csoFileNameInOut)
        {
            return D3DWriteBlobToFile(*ppBlobOut, csoFileNameInOut, FALSE);
        }
    }

    return hr;
}


使用方式如下：
ComPtr<ID3DBlob> blob;

// 创建顶点着色器
HR(CreateShaderFromFile(L"HLSL\\Triangle_VS.cso", L"HLSL\\Triangle_VS.hlsl", "VS", "vs_5_0", blob.ReleaseAndGetAddressOf()));
HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader.GetAddressOf()));
// 创建并绑定顶点布局
HR(m_pd3dDevice->CreateInputLayout(VertexPosColor::inputLayout, ARRAYSIZE(VertexPosColor::inputLayout),
    blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout.GetAddressOf()));

```




# [Windows10下开启D3D11的Debug Layer](https://www.cnblogs.com/kekec/p/14440410.html)

https://www.cnblogs.com/X-Jun/archive/2018/09/13/9638817.html
https://www.cnblogs.com/kekec/p/14440410.html





D3D Runtime是分层构造的，从核心的基本功能开始，在外部层中构建可选的功能和开发人员辅助功能。各个层（layers）只会添加功能，但不会修改现有行为。

可在调用D3D11CreateDevice或D3D11CreateDeviceAndSwapChain创建设备时并提供一个或多个D3D11_CREATE_DEVICE_FLAG值来创建层（layers）。

**核心层（Core Layer）**

核心层默认存在。在API和设备驱动程序之间提供映射，从而最大程度地减少了高频调用的开销。由于核心层对于性能至关重要，因此它仅执行关键验证。其余层是可选的。

**调试层（Debug Layer）**

调试层提供了广泛的附加参数和一致性验证（例如，验证着色器链接和资源绑定，验证参数一致性以及报告错误描述）。

若要创建支持调试层的设备，必须安装DirectX  SDK（需要D3D11SDKLayers.dll），然后在调用D3D11CreateDevice函数或D3D11CreateDeviceAndSwapChain函数时指定D3D11_CREATE_DEVICE_DEBUG标志。

如果在启用调试层的情况下运行应用程序，则该应用程序的运行速度将大大降低。但是，要确保在发布应用程序之前清除其错误和警告，请使用调试层。有关更多信息，请参阅Using the debug layer to debug apps

在DirectX SDK附带的DirectX Control Panel来启用/禁用调试标志。

当调试层列出内存泄漏时，它将输出对象接口指针及其友好名称的列表。 默认的友好名称是“ ”，开发者可使用ID3D11DeviceChild  :: SetPrivateData方法和D3Dcommon.h中的WKPDID_D3DDebugObjectName GUID来设置友好名称。

```
const char c_szName[] = "mytexture.jpg";
pTexture-SetPrivateData( WKPDID_D3DDebugObjectName, sizeof( c_szName ) - 1, c_szName );
```

**Windows10下开启D3D11的Debug Layer**

在windows 10上，带Debug Layer标志位来创建D3D11设备会失败。调试运行在Output窗口会输出如下信息：

> D3D11CreateDevice: Flags (0x2) were specified which require the D3D11 SDK Layers for Windows 10, but they are not present on the system.
> These flags must be removed, or the Windows 10 SDK must be installed.
> Flags include: D3D11_CREATE_DEVICE_DEBUG
> 。。。 。。。
> C:\Program Files (x86)\Microsoft DirectX SDK (June  2010)\samples\c++\DXUT11\Core\DXUT.cpp(3557): D3D11CreateDevice  hr=Unknown (0x887a002d)

解决方法：

1.计算机\HKEY_LOCAL_MACHINE\SOFTWARE\Policies\Microsoft\Windows\WindowsUpdate\AU下的UseWUServer设置成0，并重启计算机

\2. 安装Graphics Tools（图形工具）

# shader

语法



顶点



绘制





参数设置



## 纹理

ID3D11ShaderResourceView

ID3D11SamplerState