#pragma once
#include <d3d11.h>

class DeviceContext;

class ConstantBuffer
{
public:
	ConstantBuffer() = default;
	bool load(const void* buffer, UINT sizeBuffer);
	void update(const DeviceContext* context, const void* buffer) const;
	bool release() const;

private:
	ID3D11Buffer* constantBuffer;

	friend class DeviceContext;
};

