#pragma once
#include <d3d11.h>

class GraphicsEngine;
class DeviceContext;

class Shader
{
public:
	Shader() = default;
	virtual ~Shader() = default;

	virtual bool release() = 0;

protected:
	virtual bool init(const void* shaderByteCode, size_t byteCodeSize) = 0;

	friend class GraphicsEngine;
	friend class DeviceContext;

};

