#pragma once
#include <d3d11.h>

#include "Shader.h"

class GeometryShader : public Shader
{
public:
	GeometryShader();
	~GeometryShader() override;
	bool release() override;

private:
	bool init(const void* shaderByteCode,const size_t byteCodeSize) override;

	ID3D11GeometryShader* gs;

	friend class GraphicsEngine;
	friend class DeviceContext;
};

