#include "PixelShader.h"
#include "GraphicsEngine.h"

PixelShader::PixelShader()
= default;

PixelShader::~PixelShader()
= default;

bool PixelShader::release()
{
	ps->Release();
	delete this;

	return true;
}

bool PixelShader::init(const void* shaderByteCode, const size_t byteCodeSize)
{
	if (!SUCCEEDED(GraphicsEngine::get()->m_d3d_device->CreatePixelShader(shaderByteCode, byteCodeSize, nullptr, &ps)))
		return false;

	return true;
}
