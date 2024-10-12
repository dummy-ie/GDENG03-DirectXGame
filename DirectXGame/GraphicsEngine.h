#pragma once
#include <d3d11.h>

class ConstantBuffer;
class SwapChain;
class DeviceContext;
class VertexBuffer;
class IndexBuffer;
class VertexShader;
class GeometryShader;
class PixelShader;

class GraphicsEngine
{
public:
	static GraphicsEngine* get();
	static void initialize();
	static void destroy();

	static SwapChain* createSwapChain();
	DeviceContext* getImmediateDeviceContext() const;
	static VertexBuffer* createVertexBuffer();
	static IndexBuffer* createIndexBuffer();
	static ConstantBuffer* createConstantBuffer();
	static VertexShader* createVertexShader(const void* shaderByteCode, size_t byteCodeSize);
	static PixelShader* createPixelShader(const void* shaderByteCode, size_t byteCodeSize);
	static GeometryShader* createGeometryShader(const void* shaderByteCode, size_t byteCodeSize);

	bool compileVertexShader(const wchar_t* fileName, const char* entryPointName, void** shader_byte_code, size_t* byte_code_size);
	bool compilePixelShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize);
	bool compileGeometryShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize);
	void releaseCompiledShader() const;

private:
	GraphicsEngine();
	~GraphicsEngine();
	GraphicsEngine(GraphicsEngine const&);
	GraphicsEngine& operator=(GraphicsEngine const&) {}
	static GraphicsEngine* sharedInstance;

	bool init();
	bool release() const;

	DeviceContext* immDeviceContext = nullptr;

	ID3D11Device* d3dDevice = nullptr;
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11DeviceContext* immContext = nullptr;

	IDXGIDevice* dxgiDevice = nullptr;
	IDXGIAdapter* dxgiAdapter = nullptr;
	IDXGIFactory* dxgiFactory = nullptr;

	ID3DBlob* blob = nullptr;

	ID3DBlob* vertexShaderBlob = nullptr;
	ID3DBlob* pixelShaderBlob = nullptr;
	ID3D11VertexShader* vertexShader = nullptr;
	ID3D11PixelShader* pixelShader = nullptr;

	friend class SwapChain;
	friend class VertexBuffer;
	friend class IndexBuffer;
	friend class ConstantBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class GeometryShader;
};

