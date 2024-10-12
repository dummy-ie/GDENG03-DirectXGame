#include "ConstantBuffer.h"

#include "DeviceContext.h"
#include "GraphicsEngine.h"

bool ConstantBuffer::load(const void* buffer, const UINT sizeBuffer)
{
	if (constantBuffer)
		constantBuffer->Release();


	D3D11_BUFFER_DESC buffDesc = {};
	buffDesc.Usage = D3D11_USAGE_DEFAULT;
	buffDesc.ByteWidth = sizeBuffer;
	buffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffDesc.CPUAccessFlags = 0;
	buffDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = buffer;

	if (FAILED(GraphicsEngine::get()->d3dDevice->CreateBuffer(&buffDesc, &initData, &constantBuffer)))
		return false;

	return true;
}

void ConstantBuffer::update(const DeviceContext* context, const void* buffer) const
{
	context->deviceContext->UpdateSubresource(this->constantBuffer, NULL, nullptr, buffer, NULL, NULL);
}

bool ConstantBuffer::release() const
{
	if (constantBuffer)
		constantBuffer->Release();

	delete this;

	return true;
}
