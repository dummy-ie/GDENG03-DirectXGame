#pragma once
#include <d3d11.h>

class ConstantBuffer;
class SwapChain;
class VertexBuffer;
class IndexBuffer;
class VertexShader;
class GeometryShader;
class PixelShader;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* deviceContext);
	~DeviceContext();

	void clearRenderTargetColor(SwapChain* swapChain, float r, float g, float b, float a);
	void setVertexBuffer(VertexBuffer* vertexBuffer);
	void setIndexBuffer(IndexBuffer* indexBuffer);
	void drawTriangleList(UINT vertexCount, UINT startVertexIndex);
	void drawIndexedTriangleList(UINT indexCount, UINT startVertexIndex, UINT startIndexLocation);
	void drawTriangleStrip(UINT vertexCount, UINT startVertexIndex);
	void drawLineStrip(UINT vertexCount, UINT startVertexIndex);

	void setViewportSize(UINT width, UINT height);
	void setVertexShader(VertexShader* vertexShader);
	void setGeometryShader(GeometryShader* geometryShader);
	void setPixelShader(PixelShader* pixelShader);

	void setConstantBuffer(VertexShader* vertexShader, ConstantBuffer* constantBuffer);
	void setConstantBuffer(GeometryShader* geometryShader, ConstantBuffer* constantBuffer);
	void setConstantBuffer(PixelShader* pixelShader, ConstantBuffer* constantBuffer);

	bool release();

private:
	ID3D11DeviceContext* deviceContext;

	friend class ConstantBuffer;
};
