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
	void draw(VertexShader* vertexShader, GeometryShader* geometryShader, PixelShader* pixelShader, RECT clientWindow) override;

private:
	float deltaPos = 0;
	float deltaScale = 0;
};
