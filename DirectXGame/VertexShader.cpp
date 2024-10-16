#include "VertexShader.h"
#include "GraphicsEngine.h"

VertexShader::VertexShader()
= default;

VertexShader::~VertexShader()
= default;

bool VertexShader::release()
{
	vs->Release();
	delete this;

	return true;
}

bool VertexShader::init(const void* shaderByteCode, const size_t byteCodeSize)
{
	if (!SUCCEEDED(GraphicsEngine::get()->directXDevice->CreateVertexShader(shaderByteCode, byteCodeSize, nullptr, &vs)))
		return false;

	return true;
}
