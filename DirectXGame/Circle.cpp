#include "Circle.h"

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"

Circle::Circle(const Vec2 size, const Vector3D pos, const Vector3D pos1, const Vector3D color) : size(size), pos(pos), pos1(pos1), color(color)
{
	const int NUM_VERTICES = 64;
	std::vector<Vertex> list;

	for (int i = 0; i <= NUM_VERTICES; i += 2) {
		float angle = i * (2.0f * M_PI / NUM_VERTICES);
		float x = size.x * cos(angle);
		float y = size.y * sin(angle);

		list.push_back({ { x, y, 0.0f }, color, {1.0f, 0.0f, 0.0f} });
		list.push_back({ {0.0f, 0.0f, 0.0f}, color, {0.0f, 0.0f, 1.0f} });
	}

	void* shader_byte_code = nullptr;
	size_t byte_code_size = 0;

	vb = GraphicsEngine::get()->createVertexBuffer();
	//constexpr UINT size_list = ARRAYSIZE(list);
	UINT size_list = list.size();

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "main", &shader_byte_code, &byte_code_size);
	vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, byte_code_size);
	vb->load(list.data(), sizeof(Vertex), size_list, shader_byte_code, static_cast<UINT>(byte_code_size));
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
	Matrix4x4 temp;

	/*temp.setTranslation(Vector3D::lerp(pos, pos1, m_delta_pos));
	cc.world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));

	cc.world *= temp;*/

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
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(vb->getSizeVertexList(), 0);
}

void Circle::setVelocity(Vec2 vel)
{

}
