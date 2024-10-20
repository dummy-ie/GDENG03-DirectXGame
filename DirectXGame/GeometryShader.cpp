﻿#include "GeometryShader.h"
#include "GraphicsEngine.h"

GeometryShader::GeometryShader()
{
}

GeometryShader::~GeometryShader()
{
}

bool GeometryShader::release()
{
	gs->Release();
	delete this;

	return true;
}

bool GeometryShader::init(const void* shaderByteCode, const size_t byteCodeSize)
{
	if (!SUCCEEDED(GraphicsEngine::get()->directXDevice->CreateGeometryShader(shaderByteCode, byteCodeSize, nullptr, &gs)))
		return false;

	return true;
}
