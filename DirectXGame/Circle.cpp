#include "Circle.h"

#include "ConstantBuffer.h"
#include "DebugUtils.h"
#include "PixelShader.h"
#include "VertexShader.h"

Circle::Circle(const std::string& name, void* shaderByteCode, size_t sizeShader, const float radius) : GameObject(name)
{
	constexpr int numVertices = 64;
	std::vector<Vertex> list;

	for (int i = 0; i <= numVertices; i += 2) {
		const float angle = i * (2.0f * M_PI / numVertices);
		float x = radius * cos(angle);
		float y = radius * sin(angle);

		list.push_back({ { x, y, 0.0f }, color, {1.0f, 0.0f, 0.0f} });
		list.push_back({ {0.0f, 0.0f, 0.0f}, color, {0.0f, 0.0f, 1.0f} });
	}

	vertexBuffer = GraphicsEngine::createVertexBuffer();
	//constexpr UINT indexListSize = ARRAYSIZE(list);
	const UINT sizeList = list.size();

	vertexBuffer->load(list.data(), sizeof(Vertex), sizeList, shaderByteCode, static_cast<UINT>(sizeShader));

	Constant constants;
	constants.time = 0;

	constantBuffer = GraphicsEngine::createConstantBuffer();
	constantBuffer->load(&constants, sizeof(Constant));
}

Circle::~Circle()
{
	GameObject::~GameObject();
}

void Circle::update(const float deltaTime)
{

	deltaPos += deltaTime / 10.0f;
	if (deltaPos > 1.0f)
		deltaPos = 0;

	deltaScale += deltaTime / 0.15f;
}

void Circle::draw(VertexShader* vertexShader, GeometryShader* geometryShader, PixelShader* pixelShader, const RECT clientWindow)
{
	DeviceContext* deviceContext = GraphicsEngine::get()->getImmediateDeviceContext();
	Constant constants;
	Matrix4x4 tempMatrix;
	const float windowWidth = (clientWindow.right - clientWindow.left) / 400.f;
	const float windowHeight = (clientWindow.bottom - clientWindow.top) / 400.f;

	constants.world.setIdentity();
	constants.view.setIdentity();
	constants.proj.setOrthoLH(
		windowWidth,
		windowHeight,
		-4.0f,
		4.0f);
	constants.time = 0;

	constantBuffer->update(deviceContext, &constants);

	deviceContext->setConstantBuffer(vertexShader, constantBuffer);
	deviceContext->setConstantBuffer(geometryShader, constantBuffer);
	deviceContext->setConstantBuffer(pixelShader, constantBuffer);

	deviceContext->setVertexBuffer(vertexBuffer);
	deviceContext->drawTriangleStrip(vertexBuffer->getSizeVertexList(), 0);
}
