#include "RenderWidget.h"
#include <QDebug>
#include <QResizeEvent>
#include <QScreen>
#include <QShowEvent>
#include <QWindow>

// ------------------------------
// CreateShaderFromFile函数
// ------------------------------
// [In]csoFileNameInOut 编译好的着色器二进制文件(.cso)，若有指定则优先寻找该文件并读取
// [In]hlslFileName     着色器代码，若未找到着色器二进制文件则编译着色器代码
// [In]entryPoint       入口点(指定开始的函数)
// [In]shaderModel      着色器模型，格式为"*s_5_0"，*可以为c,d,g,h,p,v之一
// [Out]ppBlobOut       输出着色器二进制信息
HRESULT CreateShaderFromFile(const WCHAR *csoFileNameInOut,
                             const WCHAR *hlslFileName,
                             LPCSTR entryPoint,
                             LPCSTR shaderModel,
                             ID3DBlob **ppBlobOut) {
    HRESULT hr = S_OK;

    // 寻找是否有已经编译好的顶点着色器
    if (csoFileNameInOut && D3DReadFileToBlob(csoFileNameInOut, ppBlobOut) == S_OK) {
        return hr;
    } else {
        DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
        // 设置 D3DCOMPILE_DEBUG 标志用于获取着色器调试信息。该标志可以提升调试体验，
        // 但仍然允许着色器进行优化操作
        dwShaderFlags |= D3DCOMPILE_DEBUG;

        // 在Debug环境下禁用优化以避免出现一些不合理的情况
        dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
        ID3DBlob *errorBlob = nullptr;
        hr = D3DCompileFromFile(hlslFileName,
                                nullptr,
                                D3D_COMPILE_STANDARD_FILE_INCLUDE,
                                entryPoint,
                                shaderModel,
                                dwShaderFlags,
                                0,
                                ppBlobOut,
                                &errorBlob);
        if (FAILED(hr)) {
            if (errorBlob != nullptr) {
                OutputDebugStringA(reinterpret_cast<const char *>(errorBlob->GetBufferPointer()));
            }
            SAFE_RELEASE(errorBlob);
            return hr;
        }

        // 若指定了输出文件名，则将着色器二进制信息输出
        if (csoFileNameInOut) {
            return D3DWriteBlobToFile(*ppBlobOut, csoFileNameInOut, FALSE);
        }
    }

    return hr;
}

const D3D11_INPUT_ELEMENT_DESC RenderWidget::VertexPosColor::inputLayout[2]
    = {{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
       {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}};
RenderWidget::RenderWidget(QWidget *parent, Qt::WindowFlags flags) : QWidget(parent, flags) {
    //    setAttribute(Qt::WA_PaintOnScreen);
    //    setAttribute(Qt::WA_StaticContents);
    //    setAttribute(Qt::WA_NoSystemBackground);
    //    setAttribute(Qt::WA_OpaquePaintEvent);
    //    setAttribute(Qt::WA_DontCreateNativeAncestors);
    //    setAttribute(Qt::WA_NativeWindow);
    //设置窗口属性，关键步骤，否则D3D绘制出问题
    setAttribute(Qt::WA_PaintOnScreen, true);
    setAttribute(Qt::WA_NativeWindow, true);

    resize(100, 100);
    Init();
}

void RenderWidget::Init() {
    HRESULT hr;

    DXGI_MODE_DESC bufferDesc;
    ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

    bufferDesc.Width = width();
    bufferDesc.Height = height();
    bufferDesc.RefreshRate.Numerator = 60;
    bufferDesc.RefreshRate.Denominator = 1;
    bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    //Describe our SwapChain
    DXGI_SWAP_CHAIN_DESC swapChainDesc;

    ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

    swapChainDesc.BufferDesc = bufferDesc;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 1;
    swapChainDesc.OutputWindow = (HWND) winId();
    swapChainDesc.Windowed = TRUE;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    //创建设备，设备上下文，交换链
    hr = D3D11CreateDeviceAndSwapChain(NULL,
                                       D3D_DRIVER_TYPE_HARDWARE,
                                       NULL,
                                       NULL,
                                       NULL,
                                       NULL,
                                       D3D11_SDK_VERSION,
                                       &swapChainDesc,
                                       &m_swapChain,
                                       &m_d3dDevice,
                                       NULL,
                                       &m_d3dDevContext);

    //获取后台缓冲区
    ID3D11Texture2D *backBuffer;
    hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **) &backBuffer);
    if (FAILED(hr)) {
        MessageBox(NULL, L"GetBuffer Error", L"Error", NULL);
    }
    //创建渲染目标视图
    hr = m_d3dDevice->CreateRenderTargetView(backBuffer, NULL, &m_renderTargetView);
    SAFE_RELEASE(backBuffer);
    if (FAILED(hr)) {
        MessageBox(NULL, L"Create Render Target View Error", L"Error", NULL);
    }
    //Describe our Depth/Stencil Buffer  描述深度模板缓存
    D3D11_TEXTURE2D_DESC depthStencilDesc;

    depthStencilDesc.Width = width();
    depthStencilDesc.Height = height();
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.ArraySize = 1;
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilDesc.SampleDesc.Count = 1;
    depthStencilDesc.SampleDesc.Quality = 0;
    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilDesc.CPUAccessFlags = 0;
    depthStencilDesc.MiscFlags = 0;

    //Create the Depth/Stencil View// 创建深度缓冲区以及深度模板视图
    hr = m_d3dDevice->CreateTexture2D(&depthStencilDesc, NULL, &m_depthStencilBuffer);
    if (FAILED(hr)) {
        MessageBox(NULL, L"Create Depth Stencil Buffer Error", L"Error", NULL);
    }
    m_d3dDevice->CreateDepthStencilView(m_depthStencilBuffer, NULL, &m_depthStencilView);
    if (FAILED(hr)) {
        MessageBox(NULL, L"Create Depth Stencil Buffer View Error", L"Error", NULL);
    }

    //Set our Render Target
    //    m_d3dDevContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
    m_d3dDevContext->OMSetRenderTargets(1,
                                        &m_renderTargetView,
                                        nullptr); //第三个参数深度模板视图,可选
    //设置视口大小，D3D11默认不会设置视口，此步骤必须手动设置
    //Create the Viewport
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;      //视口左上角的横坐标
    viewport.TopLeftY = 0;      //视口左上角的总坐标
    viewport.Width = width();   //视口的宽
    viewport.Height = height(); //视口的高
    viewport.MinDepth = 0.0f;   //深度值的下限，**由于深度值是[0, 1]所以下限值是0
    viewport.MaxDepth = 1.0f;   //深度值的上限，上限值是1

    //Set the Viewport
    m_d3dDevContext->RSSetViewports(1, &viewport);

    /////shader
    ////    //Compile Shaders from shader file
    //    hr=D3DCompileFromFile(L"Effects.fx",0,0,"VS","vs_4_0",0,0,0,&m_pVertexShader,0,0);
    ////    hr=D3DX11CompileFromFile(L"Effects.fx",0,0,"PS","ps_4_0",0,0,0,&m_pPixelShader,0,0);
    ComPtr<ID3DBlob> blob;

    // 创建顶点着色器
    hr = CreateShaderFromFile(
        L"C:\\Users\\dxf\\Desktop\\dy-recoder\\ScreenCapture\\Triangle_VS.cso",
        L"C:\\Users\\dxf\\Desktop\\dy-recoder\\ScreenCapture\\Triangle_VS.hlsl",
        "VS",
        "vs_5_0",
        blob.ReleaseAndGetAddressOf());
    if (FAILED(hr)) {
        qDebug() << "ssss";
    }
    hr = m_d3dDevice->CreateVertexShader(blob->GetBufferPointer(),
                                         blob->GetBufferSize(),
                                         nullptr,
                                         m_pVertexShader.GetAddressOf());
    if (FAILED(hr)) {
        qDebug() << "ssss";
    }
    // 创建并绑定顶点布局
    hr = m_d3dDevice->CreateInputLayout(VertexPosColor::inputLayout,
                                        ARRAYSIZE(VertexPosColor::inputLayout),
                                        blob->GetBufferPointer(),
                                        blob->GetBufferSize(),
                                        m_pVertexLayout.GetAddressOf());
    if (FAILED(hr)) {
        qDebug() << "ssss";
    }
    // 创建像素着色器
    hr = CreateShaderFromFile(
        L"C:\\Users\\dxf\\Desktop\\dy-recoder\\ScreenCapture\\Triangle_PS.cso",
        L"C:\\Users\\dxf\\Desktop\\dy-recoder\\ScreenCapture\\Triangle_PS.hlsl",
        "PS",
        "ps_5_0",
        blob.ReleaseAndGetAddressOf());
    if (FAILED(hr)) {
        qDebug() << "ssss";
    }
    hr = m_d3dDevice->CreatePixelShader(blob->GetBufferPointer(),
                                        blob->GetBufferSize(),
                                        nullptr,
                                        m_pPixelShader.GetAddressOf());
    if (FAILED(hr)) {
        qDebug() << "ssss";
    }
    // 设置三角形顶点
    VertexPosColor vertices[] = {{XMFLOAT3(0.0f, 0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
                                 {XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)},
                                 {XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)}};
    // 设置顶点缓冲区描述
    D3D11_BUFFER_DESC vbd;
    ZeroMemory(&vbd, sizeof(vbd));
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth = sizeof vertices;
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    // 新建顶点缓冲区
    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = vertices;
    hr = m_d3dDevice->CreateBuffer(&vbd, &InitData, m_pVertexBuffer.GetAddressOf());
    if (FAILED(hr)) {
        qDebug() << "ssss";
    }
    // ******************
    // 给渲染管线各个阶段绑定好所需资源
    //

    // 输入装配阶段的顶点缓冲区设置
    UINT stride = sizeof(VertexPosColor); // 跨越字节数
    UINT offset = 0;                      // 起始偏移量

    m_d3dDevContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
    // 设置图元类型，设定输入布局
    m_d3dDevContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_d3dDevContext->IASetInputLayout(m_pVertexLayout.Get());
    // 将着色器绑定到渲染管线
    m_d3dDevContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
    m_d3dDevContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);

    // 初始化采样器状态描述
    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = m_d3dDevice->CreateSamplerState(&sampDesc, &m_sampleState);
    if (hr) {
        qDebug() << "sssssssss";
    }
}

void RenderWidget::render() {
    FLOAT color[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    m_d3dDevContext->ClearRenderTargetView(m_renderTargetView, color);
    //    m_d3dDevContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

        m_d3dDevContext->PSSetShaderResources(0, 1, &texture);//设置texture
    // Set the sampler state in the pixel shader.
        m_d3dDevContext->PSSetSamplers(0, 1, &m_sampleState);
    // 绘制三角形
    m_d3dDevContext->Draw(3, 0);
    //交换.显示到屏幕
    m_swapChain->Present(NULL, NULL);
}

void RenderWidget::resizeEvent(QResizeEvent *event) {}

void RenderWidget::paintEvent(QPaintEvent *event) {
    render();
    qDebug() << "paintEvent";
}
