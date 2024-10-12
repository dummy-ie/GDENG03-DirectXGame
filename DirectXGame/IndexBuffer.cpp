#include "IndexBuffer.h"

#include "DebugUtils.h"
#include "GraphicsEngine.h"

IndexBuffer::IndexBuffer() : indexBuffer(nullptr)
{
}

IndexBuffer::~IndexBuffer()
= default;

bool IndexBuffer::load(const void* listIndices, const UINT sizeList)
{
	if (indexBuffer)
		indexBuffer->Release();

	D3D11_BUFFER_DESC buffDesc = {};
	buffDesc.Usage = D3D11_USAGE_DEFAULT;
	buffDesc.ByteWidth = 4 * sizeList;
	buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffDesc.CPUAccessFlags = 0;
	buffDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = listIndices;

	indexListSize = sizeList;

	return DebugUtils::log(this, GraphicsEngine::get()->d3dDevice->CreateBuffer(&buffDesc, &initData, &indexBuffer));
}

bool IndexBuffer::release() const
{
	indexBuffer->Release();

	delete this;

	return true;
}

UINT IndexBuffer::getSizeIndexList() const
{
	return this->indexListSize;
}
