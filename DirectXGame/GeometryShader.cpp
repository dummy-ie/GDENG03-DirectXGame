﻿#include "GeometryShader.h"
#include "GraphicsEngine.h"
#include "LogUtils.h"

GeometryShader::GeometryShader(const void* shaderByteCode, const size_t byteCodeSize, RenderSystem* system) : GraphicsResource(system)
{
	LogUtils::log(this, system->directXDevice->CreateGeometryShader(shaderByteCode, byteCodeSize, nullptr, &gs));
}

GeometryShader::~GeometryShader()
{
	gs->Release();
}
