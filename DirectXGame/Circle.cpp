#include "Circle.h"

#include "ConstantBuffer.h"
#include "DebugUtils.h"
#include "PixelShader.h"
#include "VertexShader.h"

Circle::Circle(std::string name, void* shaderByteCode, size_t sizeShader, const float radius) : GameObject(name)
{
	const int NUM_VERTICES = 64;
	std::vector<Vertex> list;

	for (int i = 0; i <= NUM_VERTICES; i += 2) {
		float angle = i * (2.0f * M_PI / NUM_VERTICES);
		float x = radius * cos(angle);
		float y = radius * sin(angle);

		list.push_back({ { x, y, 0.0f }, color, {1.0f, 0.0f, 0.0f} });
		list.push_back({ {0.0f, 0.0f, 0.0f}, color, {0.0f, 0.0f, 1.0f} });
	}

	vb = GraphicsEngine::get()->createVertexBuffer();
	//constexpr UINT size_list = ARRAYSIZE(list);
	UINT size_list = list.size();

	DebugUtils::debugLog("loading to vertex buffer");
	vb->load(list.data(), sizeof(Vertex), size_list, shaderByteCode, static_cast<UINT>(sizeShader));
	DebugUtils::debugLog("loaded to vertex buffer");

	Constant cc;
	cc.time = 0;

	cb = GraphicsEngine::get()->createConstantBuffer();
	cb->load(&cc, sizeof(Constant));
	DebugUtils::debugLog("created const buffer");
}

void Circle::release() const
{
	vb->release();
}

void Circle::update(float deltaTime)
{
	this->angle += 1.57f * deltaTime;

	m_delta_pos += deltaTime / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;

	m_delta_scale += deltaTime / 0.15f;
}

void Circle::draw(VertexShader* vs, GeometryShader* gs, PixelShader* ps, RECT clientWindow)
{
	Constant cc;
	//cc.world.setTranslation(Vector3D(0, 0, 0));
	Matrix4x4 temp;

	//temp.setTranslation(Vector3D::lerp(pos, pos1, m_delta_pos));
	temp.setTranslation(localPosition);
	cc.world.setScale(localScale);

	cc.world *= temp;

	cc.view.setIdentity();
	cc.proj.setOrthoLH(
		(clientWindow.right - clientWindow.left) / 400.f,
		(clientWindow.bottom - clientWindow.top) / 400.f,
		-4.0f,
		4.0f);
	cc.time = 0;

	cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	std::cout << "GameObject draw: " << vs << " " << gs << " " << ps << '\n';

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vs, cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(gs, cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(ps, cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setGeometryShader(gs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(vb->getSizeVertexList(), 0);

	//GameObject::draw(vs, gs, ps, clientWindow);
}
