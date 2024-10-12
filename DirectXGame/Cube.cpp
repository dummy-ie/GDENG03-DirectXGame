#include "Cube.h"

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"

Cube::Cube(const std::string& name, void* shaderByteCode, size_t sizeShader) : GameObject(name)
{
	Vertex vertexList[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }

	};

	vertexBuffer = GraphicsEngine::createVertexBuffer();
	constexpr UINT sizeList = ARRAYSIZE(vertexList);

	unsigned int indexList[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	indexBuffer = GraphicsEngine::createIndexBuffer();
	constexpr UINT sizeIndexList = ARRAYSIZE(indexList);

	indexBuffer->load(indexList, sizeIndexList);
	vertexBuffer->load(
		vertexList,
		sizeof(Vertex),
		sizeList,
		shaderByteCode,
		static_cast<UINT>(sizeShader));

	Constant constants;
	constants.time = 0;

	constantBuffer = GraphicsEngine::createConstantBuffer();
	constantBuffer->load(&constants, sizeof(Constant));
}

Cube::~Cube()
{
	GameObject::~GameObject();
}

void Cube::update(float deltaTime)
{
	deltaPos += deltaTime / 10.0f;
	if (deltaPos > 1.0f)
		deltaPos = 0;

	deltaScale += deltaTime / 1.0f;
}

void Cube::draw(VertexShader* vertexShader, GeometryShader* geometryShader, PixelShader* pixelShader, RECT clientWindow)
{
	DeviceContext* deviceContext = GraphicsEngine::get()->getImmediateDeviceContext();
	Constant constants;
	Matrix4x4 tempMatrix;
	const float windowWidth = (clientWindow.right - clientWindow.left) / 400.f;
	const float windowHeight = (clientWindow.bottom - clientWindow.top) / 400.f;

	constants.world.setTranslation(localPosition);
	constants.world.setScale(localScale);

	tempMatrix.setIdentity();
	tempMatrix.setRotationZ(localRotation.z);
	constants.world *= tempMatrix;

	tempMatrix.setIdentity();
	tempMatrix.setRotationY(localRotation.y);
	constants.world *= tempMatrix;

	tempMatrix.setIdentity();
	tempMatrix.setRotationX(localRotation.x);
	constants.world *= tempMatrix;

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
	deviceContext->setIndexBuffer(indexBuffer);

	deviceContext->drawIndexedTriangleList(indexBuffer->getSizeIndexList(), 0, 0);
	// deviceContext->drawTriangleStrip(vertexBuffer->getSizeVertexList(), 0);
}
