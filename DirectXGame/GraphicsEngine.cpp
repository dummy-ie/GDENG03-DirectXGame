#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "GeometryShader.h"
#include <d3dcompiler.h>

#include "DebugUtils.h"

GraphicsEngine* GraphicsEngine::sharedInstance = nullptr;


GraphicsEngine::GraphicsEngine()
= default;

GraphicsEngine::~GraphicsEngine()
= default;

GraphicsEngine::GraphicsEngine(GraphicsEngine const&)
{}

bool GraphicsEngine::init()
{
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		res = D3D11CreateDevice(
			nullptr,
			driverTypes[driver_type_index],
			nullptr,
			NULL,
			feature_levels,
			num_feature_levels,
			D3D11_SDK_VERSION,
			&d3dDevice,
			&featureLevel,
			&immContext);

		if (SUCCEEDED(res))
			break;

		++driver_type_index;
	}

	if (FAILED(res))
		return false;

	immDeviceContext = new DeviceContext(immContext);

	d3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
	dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&dxgiAdapter));
	dxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&dxgiFactory));

	return true;
}

bool GraphicsEngine::release() const
{
	dxgiDevice->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();

	immDeviceContext->release();

	immContext->Release();
	d3dDevice->Release();

	return true;
}

SwapChain* GraphicsEngine::createSwapChain()
{
	return new SwapChain();
}

DeviceContext* GraphicsEngine::getImmediateDeviceContext() const
{
	return this->immDeviceContext;
}

VertexBuffer* GraphicsEngine::createVertexBuffer()
{
	return new VertexBuffer();
}

IndexBuffer* GraphicsEngine::createIndexBuffer()
{
	return new IndexBuffer();
}

ConstantBuffer* GraphicsEngine::createConstantBuffer()
{
	return new ConstantBuffer();
}

VertexShader* GraphicsEngine::createVertexShader(const void* shaderByteCode, size_t byteCodeSize)
{
	VertexShader* vs = new VertexShader();
	if (!vs->init(shaderByteCode, byteCodeSize))
	{
		vs->release();
		return nullptr;
	}
	return vs;
}

PixelShader* GraphicsEngine::createPixelShader(const void* shaderByteCode, size_t byteCodeSize)
{
	PixelShader* ps = new PixelShader();
	if (!ps->init(shaderByteCode, byteCodeSize))
	{
		ps->release();
		return nullptr;
	}
	return ps;
}

GeometryShader* GraphicsEngine::createGeometryShader(const void* shaderByteCode, const size_t byteCodeSize)
{
	GeometryShader* gs = new GeometryShader();
	if (!gs->init(shaderByteCode, byteCodeSize))
	{
		gs->release();
		return nullptr;
	}
	return gs;
}

bool GraphicsEngine::compileGeometryShader(const wchar_t* fileName, const char* entryPointName,
	void** shaderByteCode, size_t* byteCodeSize)
{
	ID3DBlob* errorBlob = nullptr;
	if (FAILED(::D3DCompileFromFile(
		fileName,
		nullptr,
		nullptr,
		entryPointName,
		"gs_5_0",
		0,
		0,
		&blob,
		&errorBlob)))
	{
		if (errorBlob)
		{
			DebugUtils::error(this, "Geometry shader compilation failed!");
			errorBlob->Release();
		}

		return false;
	}

	*shaderByteCode = blob->GetBufferPointer();
	*byteCodeSize = blob->GetBufferSize();

	return true;
}

bool GraphicsEngine::compileVertexShader(const wchar_t* fileName, const char* entryPointName, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (FAILED(::D3DCompileFromFile(
		fileName,
		nullptr,
		nullptr,
		entryPointName,
		"vs_5_0",
		0,
		0,
		&blob,
		&error_blob
	)))
	{
		if (error_blob)
		{
			DebugUtils::error(this, "Vertex shader compilation failed!");
			error_blob->Release();
		}

		return false;
	}

	*shader_byte_code = blob->GetBufferPointer();
	*byte_code_size = blob->GetBufferSize();

	return true;
}

bool GraphicsEngine::compilePixelShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode,
	size_t* byteCodeSize)
{
	ID3DBlob* errorBlob = nullptr;
	if (FAILED(::D3DCompileFromFile(
		fileName,
		nullptr,
		nullptr,
		entryPointName,
		"ps_5_0",
		0,
		0,
		&blob,
		&errorBlob
	)))
	{
		if (errorBlob)
		{
			DebugUtils::error(this, "Pixel shader compilation failed!");
			errorBlob->Release();
		}

		return false;
	}

	*shaderByteCode = blob->GetBufferPointer();
	*byteCodeSize = blob->GetBufferSize();

	return true;
}

void GraphicsEngine::releaseCompiledShader() const
{
	if (blob)
		blob->Release();
}

GraphicsEngine* GraphicsEngine::get()
{
	// if (!sharedInstance)
	// sharedInstance = new GraphicsEngine();
	return sharedInstance;
}

void GraphicsEngine::initialize()
{
	sharedInstance = new GraphicsEngine();
	sharedInstance->init();
}

void GraphicsEngine::destroy()
{
	if (sharedInstance != nullptr)
		sharedInstance->release();

	delete sharedInstance;
}
