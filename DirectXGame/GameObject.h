#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "Vectors.h"
#include "Vertex.h"
#include "Constant.h"
#include "ConstantBuffer.h"

class GameObject
{
public:
	explicit GameObject(std::string name) : name(std::move(name))
	{
	}

	virtual ~GameObject()
	{
		if (vertexBuffer)
			vertexBuffer->release();

		if (indexBuffer)
			indexBuffer->release();

		if (constantBuffer)
			constantBuffer->release();
	}

	virtual void update(float deltaTime) = 0;
	virtual void draw(VertexShader* vertexShader, GeometryShader* geometryShader, PixelShader* pixelShader, RECT clientWindow) = 0;

	void setPosition(const Vector3D& position) { localPosition = position; }
	void setScale(const Vector3D& scale) { localScale = scale; }
	void setRotation(const Vector3D& rotation) { localRotation = rotation; }

protected:
	std::string name;

	Vector3D localScale = 0.5f;
	Vector3D localPosition = 0.f;
	Vector3D localRotation = 0.f;

	Vector3D color;

	VertexBuffer* vertexBuffer = nullptr;
	IndexBuffer* indexBuffer = nullptr;
	ConstantBuffer* constantBuffer = nullptr;
};
