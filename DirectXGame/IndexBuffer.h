#pragma once
#include <d3d11.h>

class DeviceContext;

class IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();

	bool load(const void* listIndices, UINT sizeList);
	bool release() const;

	UINT getSizeIndexList() const;

private:
	UINT indexListSize;

	ID3D11Buffer* indexBuffer;

	friend class DeviceContext;
};

