#pragma once
#define _USE_MATH_DEFINES // Before including <cmath>
#include <cmath>
#include <vector>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "Vectors.h"
#include "Vertex.h"
#include "Constant.h"
#include "GameObject.h"

class Circle : public GameObject
{
public:
	Circle(std::string name, void* shaderByteCode, size_t sizeShader, const float radius);

	void release() const override;

	void update(float deltaTime) override;
	void draw(VertexShader* vs, GeometryShader* gs, PixelShader* ps, RECT clientWindow) override;

private:
	float m_delta_pos = 0;
	float m_delta_scale = 0;

	float angle = 0;
};
