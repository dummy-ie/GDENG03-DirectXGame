#include "Circle.h"

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"

Circle::Circle(const Vec2 size, const Vector3D pos, const Vector3D pos1, const Vector3D color) : size(size), pos(pos), pos1(pos1), color(color)
{
	// Vertex list[] =
	// {
	// 	{
	// 		{-size.x + pos.x, -size.y + pos.y, 0.0f},
	// 		{-size.x + pos1.x, -size.y + pos1.y, 0.0f},
	// 		color,
	// 		{0, 1, 0}},
	//
	// 	{
	// 		{-size.x + pos.x, size.y + pos.y, 0.0f},
	// 		{-size.x + pos1.x, size.y + pos1.y, 0.0f},
	// 		color,
	// 		{	0, 1, 1}},
	//
	// 	{
	// 		{size.x + pos.x, -size.y + pos.y, 0.0f},
	// 		{size.x + pos1.x, -size.y + pos1.y, 0.0f},
	// 		color,
	// 		{	1, 0, 0}},
	//
	// 	{
	// 		{size.x + pos.x, size.y + pos.y, 0.0f},
	// 		{size.x + pos1.x, size.y + pos1.y, 0.0f},
	// 		color,
	// 		{0, 0, 1}}
	// };

	//Vertex list[] =
	//{
	//	//X - Y - Z
	//	{Vector3D(-0.5f,-0.5f,0.0f),      Vector3D(0,0,0), Vector3D(0,1,0) }, // POS1
	//	{Vector3D(-0.5f,0.5f,0.0f),        Vector3D(1,1,0), Vector3D(0,1,1) }, // POS2
	//	{ Vector3D(0.5f,-0.5f,0.0f),      Vector3D(0,0,1),  Vector3D(1,0,0) },// POS2
	//	{ Vector3D(0.5f,0.5f,0.0f),        Vector3D(1,1,1), Vector3D(0,0,1) }
	//};

	//int n = 10; // number of triangles
	//Vertex* vertices = malloc(sizeof(SimpleVertex) * 10 * 3); // 10 triangles, 3 verticies per triangle
	//float deltaTheta = 2 * pi / n; // Change in theta for each vertex
	//for (int i = 0; i < n; i++) {
	//	int theta = i * deltaTheta; // Theta is the angle for that triangle
	//	int index = 3 * i;
	//	vertices[index + 0] = SimpleVertex(0, 0, 0);
	//	// Given an angle theta, cosine [cos] will give you the x coordinate,
	//	// and sine [sin] will give you the y coordinate.
	//	// #include <math.h>
	//	vertices[index + 1] = SimpleVertex(cos(theta), sin(theta), 0);
	//	vertices[index + 2] = SimpleVertex(cos(theta + deltaTheta), sin(theta + deltaTheta), 0);
	//}

	const int NUM_VERTICES = 30;
	Vertex list[NUM_VERTICES * 3];


	list[0] = { pos, color, color };

	for (int i = 1; i <= NUM_VERTICES; ++i) {
		float angle = (i * 2.0f * M_PI) / NUM_VERTICES;
		float x = pos.x + size.x * cos(angle);
		float y = pos.y + size.y * sin(angle);

		list[i] = { { x, y, 0.0f }, color, color }; // Red color

		if (i % 3 == 0)
		{
			list[0] = { pos, color, color };
		}
	}

	/*vertices.push_back({ pos, color });

	for (int i = 0; i <= NUM_VERTICES; ++i) {
		float angle = (i * 2.0f * M_PI) / NUM_VERTICES;
		float x = size.x * cos(angle);
		float y = size.y * sin(angle);

		vertices.push_back({ { x, y, 0.0f }, color });
	}*/

	void* shader_byte_code = nullptr;
	size_t byte_code_size = 0;

	vb = GraphicsEngine::get()->createVertexBuffer();
	constexpr UINT size_list = ARRAYSIZE(list);

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "main", &shader_byte_code, &byte_code_size);
	vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, byte_code_size);
	vb->load(list, sizeof(Vertex), size_list, shader_byte_code, static_cast<UINT>(byte_code_size));
	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compileGeometryShader(L"GeometryShader.hlsl", "main", &shader_byte_code, &byte_code_size);
	gs = GraphicsEngine::get()->createGeometryShader(shader_byte_code, byte_code_size);
	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "main", &shader_byte_code, &byte_code_size);
	ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, byte_code_size);
	GraphicsEngine::get()->releaseCompiledShader();

	Constant cc;
	cc.time = 0;

	cb = GraphicsEngine::get()->createConstantBuffer();
	cb->load(&cc, sizeof(Constant));
}

void Circle::release() const
{
	vb->release();
	vs->release();
	ps->release();
}

void Circle::draw(float deltaTime, RECT clientWindow)
{
	this->angle += 1.57f * deltaTime;

	m_delta_pos += deltaTime / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;

	m_delta_scale += deltaTime / 0.15f;

	Constant cc;
	//cc.world.setTranslation(Vector3D(0, 0, 0));
	Matrix4x4 temp;

	// temp.setTranslation(Vector3D::lerp(pos, pos1, m_delta_pos));
	// cc.world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));
	// 
	// cc.world *= temp;

	cc.world.setIdentity();
	cc.view.setIdentity();
	cc.proj.setOrthoLH(
		(clientWindow.right - clientWindow.left) / 400.f,
		(clientWindow.bottom - clientWindow.top) / 400.f,
		-4.0f,
		4.0f);
	cc.time = angle;

	cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vs, cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(gs, cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(ps, cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setGeometryShader(gs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(vb->getSizeVertexList() + 2, 0);
}

void Circle::setVelocity(Vec2 vel)
{

}
