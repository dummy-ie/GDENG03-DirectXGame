#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "Vectors.h"
#include "Vertex.h"
#include "Constant.h"
#include "GameObject.h"

class Quad
{
public:

	explicit Quad(
		Vec2 size = { 0.1f, 0.1f },
		Vector3D pos = { 0.0f, 0.0f, 0.0f },
		Vector3D pos1 = { 0.0f, 0.0f, 0.0f },
		Vector3D color = Vector3D( 1.0f, 1.0f, 1.0f ));

	void release() const;
	void draw(float deltaTime, RECT clientWindow);

private:
	float m_delta_pos = 0;
	float m_delta_scale = 0;
	Vec2 size;
	Vector3D pos;
	Vector3D pos1;
	Vector3D color;
	float angle = 0;
	VertexBuffer* vb;
	IndexBuffer* ib;
	ConstantBuffer* cb;
	VertexShader* vs;
	GeometryShader* gs;
	PixelShader* ps;
};
