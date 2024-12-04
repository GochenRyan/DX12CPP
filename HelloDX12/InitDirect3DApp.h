#pragma once

#include "d3dApp.h"

class InitDirect3DApp : public D3DApp
{
public:
	InitDirect3DApp(HINSTANCE hInstance);
    InitDirect3DApp(const InitDirect3DApp& rhs) = delete;
    InitDirect3DApp& operator=(const InitDirect3DApp& rhs) = delete;
	~InitDirect3DApp();

	virtual bool Initialize() override;

private:
    virtual void OnResize() override;
    virtual void Update(const GameTimer& gt) override;
    virtual void Draw(const GameTimer& gt) override;
};