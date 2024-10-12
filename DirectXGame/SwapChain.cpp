#include "SwapChain.h"

#include "DebugUtils.h"

SwapChain::SwapChain()
= default;

SwapChain::~SwapChain()
= default;

bool SwapChain::init(const HWND windowHandle, const UINT width, const UINT height)
{
	ID3D11Device* device = GraphicsEngine::get()->d3dDevice;
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = windowHandle;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	HRESULT hr = DebugUtils::log(this, GraphicsEngine::get()->dxgiFactory->CreateSwapChain(device, &desc, &swapChain));

	if (FAILED(hr))
		return false;

	ID3D11Texture2D* buffer = nullptr;
	hr = DebugUtils::log(this, swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&buffer)));

	if (FAILED(hr))
		return false;

	hr = device->CreateRenderTargetView(buffer, nullptr, &renderTargetView);
	buffer->Release();

	if (FAILED(hr))
		return false;

	return true;
}

bool SwapChain::release() const
{
	swapChain->Release();
	delete this;

	return true;
}

bool SwapChain::present(const bool vsync) const
{
	DebugUtils::log(this, swapChain->Present(vsync, NULL));

	return true;
}
