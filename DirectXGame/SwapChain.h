#pragma once
#include "GraphicsEngine.h"
#include <d3d11.h>

class DeviceContext;

class SwapChain
{
public:
	SwapChain();
	~SwapChain();
	bool init(HWND windowHandle, UINT width, UINT height);
	bool release() const;
	bool present(bool vsync) const;

private:
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* renderTargetView;

	friend class DeviceContext;
};

