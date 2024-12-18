#pragma once

#include "d3dUtil.h"
#include "GameTimer.h"

class D3DApp
{
protected:
    D3DApp(HINSTANCE hInstance);
    D3DApp(const D3DApp&) = delete;
    D3DApp(D3DApp&&) = default;
    D3DApp& operator=(const D3DApp&) = delete;
    D3DApp& operator=(D3DApp&&) = default;
    virtual ~D3DApp();

public:
    static D3DApp* GetApp();
    HINSTANCE AppInst() const;
    HWND MainWnd() const;
    float AspectRatio() const;

    bool Get4xMsaaState() const;
    void Set4xMsaaState(bool value);

    int Run();
    virtual bool Initialize();
    virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
    bool InitMainWindow();
    bool InitDirect3D();
    void CreateCommandObjects();
    void CreateSwapChain();

    void FlushCommandQueue();

    ID3D12Resource* CurrentBackBuffer()const;
    D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView() const;
    D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView() const;
    void CalculateFrameStats();

protected:
    virtual void CreateRtvAndDsvDescriptorHeaps();
    virtual void OnResize(); 
    virtual void Update(const GameTimer& gt)=0;
    virtual void Draw(const GameTimer& gt)=0;

    virtual void OnMouseDown(WPARAM btnState, int x, int y) {}
    virtual void OnMouseMove(WPARAM btnState, int x, int y) {}
    virtual void OnMouseUp(WPARAM btnState, int x, int y) {}

protected:
    static D3DApp* mApp;

    HINSTANCE mhAppInst = nullptr; // application instance handle
    HWND mhMainWnd = nullptr; // main window handle

    bool mAppPaused = false;  // is the application paused?
    bool mMinimized = false;  // is the application minimized?
    bool mMaximized = false;  // is the application maximized?
    bool mResizing = false;   // are the resize bars being dragged?
    bool mFullscreenState = false;// fullscreen enabled

    Microsoft::WRL::ComPtr<IDXGIFactory4> mdxgiFactory;
    Microsoft::WRL::ComPtr<ID3D12Device> md3dDevice;
    
    Microsoft::WRL::ComPtr<ID3D12Fence> mFence;
    UINT64 mCurrentFence = 0;

    Microsoft::WRL::ComPtr<ID3D12CommandQueue> mCommandQueue;
    Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mDirectCmdListAlloc;
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCommandList;
    Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mRtvHeap;  // Render Target View
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mDsvHeap;  // Depth / Stencil View

    D3D12_VIEWPORT mScreenViewport; 
    D3D12_RECT mScissorRect;

    UINT mRtvDescriptorSize = 0;
    UINT mDsvDescriptorSize = 0;
    UINT mCbvSrvUavDescriptorSize = 0;  // Constant Buffer View, Shader Resource View, Unordered access view

    DXGI_FORMAT mBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
    DXGI_FORMAT mDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

    // Derived class should set these in derived constructor to customize starting values.
    std::wstring mMainWndCaption = L"d3d App";

    int mClientWidth = 800;
    int mClientHeight = 600;

    bool m4xMsaaState = false;    // 4X MSAA enabled
    UINT m4xMsaaQuality = 0;      // quality level of 4X MSAA
    
    static const int SwapChainBufferCount = 2;
    int mCurrBackBuffer = 0;
    Microsoft::WRL::ComPtr<ID3D12Resource> mSwapChainBuffer[SwapChainBufferCount];
    Microsoft::WRL::ComPtr<ID3D12Resource> mDepthStencilBuffer;

    // Used to keep track of the “delta-time” and game time.
    GameTimer mTimer;
};

