#include "DeviceContext.h"

#include "PixelShader.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "GeometryShader.h"
#include "IndexBuffer.h"
#include "PixelShader.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext) : deviceContext(deviceContext)
{

}

DeviceContext::~DeviceContext()
= default;

void DeviceContext::clearRenderTargetColor(SwapChain* swapChain, float r, float g, float b, float a)
{
	const FLOAT clearColor[] = { r, g, b, a };
	deviceContext->ClearRenderTargetView(swapChain->renderTargetView, clearColor);
	deviceContext->OMSetRenderTargets(1, &swapChain->renderTargetView, nullptr);
}

void DeviceContext::setVertexBuffer(VertexBuffer* vertexBuffer)
{
	UINT stride = vertexBuffer->m_size_vertex;
	UINT offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer->m_buffer, &stride, &offset);
	deviceContext->IASetInputLayout(vertexBuffer->m_layout);
}

void DeviceContext::setIndexBuffer(IndexBuffer* indexBuffer)
{
	deviceContext->IASetIndexBuffer(indexBuffer->indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void DeviceContext::drawTriangleList(UINT vertexCount, UINT startVertexIndex)
{
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::drawIndexedTriangleList(UINT indexCount, UINT startVertexIndex, UINT startIndexLocation)
{
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->DrawIndexed(indexCount, startIndexLocation, startVertexIndex);
}

void DeviceContext::drawTriangleStrip(UINT vertexCount, UINT startVertexIndex)
{
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	deviceContext->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::drawLineStrip(UINT vertexCount, UINT startVertexIndex)
{
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	deviceContext->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::setViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT vp = {};
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.f;
	vp.MaxDepth = 1.f;


	deviceContext->RSSetViewports(1, &vp);
}

void DeviceContext::setVertexShader(VertexShader* vertexShader)
{
	deviceContext->VSSetShader(vertexShader->vs, nullptr, 0);
}

void DeviceContext::setGeometryShader(GeometryShader* geometryShader)
{
	deviceContext->GSSetShader(geometryShader->gs, nullptr, 0);
}

void DeviceContext::setPixelShader(PixelShader* pixelShader)
{
	deviceContext->PSSetShader(pixelShader->ps, nullptr, 0);
}

void DeviceContext::setConstantBuffer(VertexShader* vertexShader, ConstantBuffer* constantBuffer)
{
	deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer->constantBuffer);
}

void DeviceContext::setConstantBuffer(GeometryShader* geometryShader, ConstantBuffer* constantBuffer)
{
	deviceContext->GSSetConstantBuffers(0, 1, &constantBuffer->constantBuffer);
}


void DeviceContext::setConstantBuffer(PixelShader* pixelShader, ConstantBuffer* constantBuffer)
{
	deviceContext->PSSetConstantBuffers(0, 1, &constantBuffer->constantBuffer);
}

bool DeviceContext::release()
{
	deviceContext->Release();
	delete this;

	return true;
}
