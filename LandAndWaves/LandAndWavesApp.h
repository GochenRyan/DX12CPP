#pragma once

#include "d3dApp.h"
#include "FrameResource.h"
#include "RenderItem.h"
#include "UploadBuffer.h"

class LandAndWavesApp : public D3DApp
{
public:
    LandAndWavesApp(HINSTANCE hInstance);
    LandAndWavesApp(const LandAndWavesApp& rhs) = delete;
    LandAndWavesApp& operator=(const LandAndWavesApp& rhs) = delete;
    ~LandAndWavesApp();

    virtual bool Initialize() override;

private:
    virtual void OnResize() override;
    virtual void Update(const GameTimer& gt) override;
    virtual void Draw(const GameTimer& gt) override;

    virtual void OnMouseDown(WPARAM btnState, int x, int y) override;
    virtual void OnMouseUp(WPARAM btnState, int x, int y) override;
    virtual void OnMouseMove(WPARAM btnState, int x, int y) override;

    void OnKeyboardInput(const GameTimer& gt);
    void UpdateCamera(const GameTimer& gt);
    void UpdateObjectCBs(const GameTimer& gt);
    void UpdateMainPassCB(const GameTimer& gt);
    void UpdateWaves(const GameTimer& gt);


    void BuildRootSignature();
    void BuildShaderAndInputLayout();
    void BuildLandGeometry();
    void BuildRenderItems();
    void BuildFrameResources();
    void BuildPSOs();

    void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);

    float GetHillsHeight(float x, float z) const;
    DirectX::XMFLOAT3 GetHillsNormal(float x, float z) const;

private:
    std::vector<std::unique_ptr<FrameResource>> mFrameResources;
    FrameResource* mCurrFrameResource = nullptr;
    int mCurrFrameResourceIndex = 0;

    Microsoft::WRL::ComPtr<ID3D12RootSignature> mRootSignature = nullptr;;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mCbvHeap = nullptr;

    std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
    std::unordered_map<std::string, ComPtr<ID3DBlob>> mShaders;
    std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> mPSOs;

    Microsoft::WRL::ComPtr<ID3D12PipelineState> mPSO = nullptr;

    std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;
    // List of all the render items.
    std::vector<std::unique_ptr<RenderItem>> mAllRitems;
    // Render items divided by PSO.
    std::vector<RenderItem*> mOpaqueRitems;

    PassConstants mMainPassCB;

    std::unique_ptr<UploadBuffer<ObjectConstants>> mObjectCB = nullptr;

    Microsoft::WRL::ComPtr<ID3DBlob> mvsByteCode = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> mpsByteCode = nullptr;

    DirectX::XMFLOAT3 mEyePos = { 0.0f, 0.0f, 0.0f };
    DirectX::XMFLOAT4X4 mView = MathHelper::Identity4x4();
    DirectX::XMFLOAT4X4 mProj = MathHelper::Identity4x4();

    // Indicates the angle measured downward from the positive Y axis
    float mTheta = 1.5f * DirectX::XM_PI;
    // The angle between the point on the XZ plane and the positive direction of the X axis
    float mPhi = 0.2f * XM_PI;
    float mRadius = 15.0f;

    POINT mLastMousePos;

    UINT mPassCbvOffset = 0;
    
    bool mIsWireframe = false;
};