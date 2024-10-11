#pragma once
#include <d3d11.h>

#include "Shader.h"

class VertexShader : public Shader
{
public:
	VertexShader();
	~VertexShader() override;

	bool release() override;

private:
	bool init(const void* shaderByteCode,const size_t byteCodeSize) override;

	ID3D11VertexShader* vs;

	friend class GraphicsEngine;
	friend class DeviceContext;
};

