#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "Vectors.h"
#include "Vertex.h"
#include "Constant.h"

class GameObject
{
public:

	GameObject(const std::string& name) : name(name) {};
	virtual ~GameObject() = default;

	virtual void release() const = 0;

	virtual void update(float deltaTime) = 0;
	virtual void draw(VertexShader* vs, GeometryShader* gs, PixelShader* ps, RECT clientWindow) = 0;

	void setPosition(const Vector3D& pos) { localPosition = pos; }
	void setScale(const Vector3D& sca) { localScale = sca; }
	void setRotation(const Vector3D& rot) { localRotation = rot; }

protected:
	float deltaPos = 0;
	float deltaScale = 0;

	std::string name;

	Vector3D localScale;
	Vector3D localPosition;
	Vector3D localRotation;

	Vector3D color;

	VertexBuffer* vb;
	IndexBuffer* ib;
	ConstantBuffer* cb;
};
