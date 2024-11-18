#pragma once

#include "d3dUtil.h"
#include "GameTimer.h"

class D3DApp
{
public:
    static D3DApp& Instance()
    {
        static D3DApp instance;
        return instance;
    }

    D3DApp(const D3DApp&) = delete;
    D3DApp(D3DApp&&) = default;
    D3DApp& operator=(const D3DApp&) = delete;
    D3DApp& operator=(D3DApp&&) = default;
    virtual ~D3DApp();

protected:
    D3DApp() = default;
    void InitDirect3D();
    void CreateCommandObjects();
    void CreateSwapChain();
    D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView() const;
    D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView() const;
    void CalculateFrameStats();

protected:
    virtual void CreateRtvAndDsvDescriptorHeaps();
    virtual void OnResize(); 

protected:
    HWND mhMainWnd = nullptr; // main window handle

    Microsoft::WRL::ComPtr<IDXGIFactory4> mdxgiFactory;
    Microsoft::WRL::ComPtr<ID3D12Device> md3dDevice;
    Microsoft::WRL::ComPtr<ID3D12Fence> mFence;
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> mCommandQueue;
    Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mDirectCmdListAlloc;
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCommandList;
    Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mRtvHeap;  // Render Target View
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mDsvHeap;  // Depth / Stencil View

    D3D12_VIEWPORT mScreenViewport; 
    D3D12_RECT mScissorRect;

    UINT mRtvDescriptorSize;
    UINT mDsvDescriptorSize;
    UINT mCbvUavDescriptorSize;

    UINT m4xMsaaQuality;

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

