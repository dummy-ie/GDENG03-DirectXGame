#pragma once
#include <d3d11.h>

#include "Shader.h"

class PixelShader : public Shader
{
public:
	PixelShader();
	~PixelShader() override;
	bool release() override;

private:
	bool init(const void* shaderByteCode, const size_t byteCodeSize) override;

	ID3D11PixelShader* ps;

	friend class GraphicsEngine;
	friend class DeviceContext;
};

