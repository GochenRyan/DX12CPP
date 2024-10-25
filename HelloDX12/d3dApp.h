#pragma once

#include "d3dUtil.h"
#include "GameTimer.h"

class D3DApp
{
protected:
    void InitDirect3D();

private:
    Microsoft::WRL::ComPtr<IDXGIFactory4> mdxgiFactory;
    Microsoft::WRL::ComPtr<ID3D12Device> md3dDevice;
    Microsoft::WRL::ComPtr<ID3D12Fence> mFence;

    UINT mRtvDescriptorSize;
    UINT mDsvDescriptorSize;
    UINT mCbvUavDescriptorSize;

    UINT m4xMsaaQuality;

    DXGI_FORMAT mBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
};