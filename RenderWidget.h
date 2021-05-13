#pragma once

#include <QWidget>
//包含D3D相关的头文件
#include <d3d11.h>
#include <wrl/client.h>
#include <d3dcompiler.h>
using namespace Microsoft::WRL;
//#include <d3dx10.h>
//#include <d3dx11.h>
#include <DirectXMath.h>
using namespace DirectX;
//安全释放COM口定义的宏
#define SAFE_RELEASE(p) \
    { \
        if (p) { \
            (p)->Release(); \
            p = 0; \
        } \
    }

class RenderWidget : public QWidget {
    Q_OBJECT
public:
    struct VertexPosColor
    {
        DirectX::XMFLOAT3 pos;
        DirectX::XMFLOAT4 color;
        static const D3D11_INPUT_ELEMENT_DESC inputLayout[2];
    };
    RenderWidget(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    virtual QPaintEngine *paintEngine() const { return nullptr; }
    void Init();
    void render();

private:
    //重写虚函数
    virtual void resizeEvent(QResizeEvent *event); //当窗口尺寸改变时响应
    virtual void paintEvent(QPaintEvent *event);   //窗口绘制函数，用于render三维场景
                                                   //    //键盘和鼠标监听
    //    virtual void keyPressEvent(QKeyEvent *event);
    //    virtual void keyReleaseEvent(QKeyEvent *event);
    //    virtual void mousePressEvent(QMouseEvent *event);
    //    virtual void mouseReleaseEvent(QMouseEvent *event);
    //    virtual void mouseMoveEvent(QMouseEvent *event);
    //    virtual void wheelEvent(QWheelEvent *event);

    //D3D相关的变量
    ID3D11Device *m_d3dDevice = nullptr;
    ID3D11DeviceContext *m_d3dDevContext = nullptr;
    IDXGISwapChain *m_swapChain = nullptr;
    ID3D11DepthStencilView *m_depthStencilView = nullptr; //深度模板视图
    ID3D11RenderTargetView *m_renderTargetView = nullptr; //渲染目标视图
    ID3D11Texture2D *m_depthStencilBuffer;

    ComPtr<ID3D11InputLayout> m_pVertexLayout;  // 顶点输入布局
    ComPtr<ID3D11Buffer> m_pVertexBuffer;       // 顶点缓冲区
    ComPtr<ID3D11VertexShader> m_pVertexShader; // 顶点着色器
    ComPtr<ID3D11PixelShader> m_pPixelShader;   // 像素着色器

};
