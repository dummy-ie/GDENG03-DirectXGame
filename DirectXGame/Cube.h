#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "Vectors.h"
#include "Vertex.h"
#include "Constant.h"
#include "GameObject.h"

class Cube : public GameObject
{
public:

	Cube(const std::string& name, void* shaderByteCode, size_t sizeShader);
	~Cube() override;

	void update(float deltaTime) override;
	void draw(VertexShader* vertexShader, GeometryShader* geometryShader, PixelShader* pixelShader, RECT clientWindow) override;

private:
	float deltaPos = 0.0f;
	float deltaScale = 0.0f;
	float animationSpeed = 1.0f;
};
