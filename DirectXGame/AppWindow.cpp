#include "AppWindow.h"

#include "InputSystem.h"

AppWindow* AppWindow::sharedInstance = nullptr;

AppWindow* AppWindow::get()
{
	return sharedInstance;
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
	sharedInstance->init();
}

void AppWindow::destroy()
{
	if (sharedInstance != NULL)
		sharedInstance->release();

	delete sharedInstance;
}

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onKeyDown(int key)
{
	switch (key)
	{
	default:
		break;
	}
}

void AppWindow::onKeyUp(int key)
{
	switch (key)
	{
	case VK_SPACE:
	{
		// float randsize = randrange_float(0.1f, 1.0f);
		// Vec2 size = { randsize, randsize };
		// Vector3D pos = { randrange_float(-0.8f, 0.8f), randrange_float(-0.8f, 0.8f), randrange_float(-0.8f, 0.8f) };
		//
		// std::cout << "position: " << pos << std::endl;
		// circleVector.emplace_back(size, pos);
		//circleVector.emplace_back();
		break;
	}
	case VK_ESCAPE:
		exit(0);
		break;
		// case VK_DELETE:
		// 	circleVector.clear();
		// 	break;
		// case VK_BACK:
		// {
		// 	if (!circleVector.empty())
		// 		circleVector.pop_back();
		// 	break;
		// }
	default:
		break;
	}
}

void AppWindow::onCreate()
{
	Window::onCreate();

	//GraphicsEngine::get()->init();
	GraphicsEngine::initialize();
	swapChain = GraphicsEngine::get()->createSwapChain();

	const RECT rc = this->getClientWindowRect();
	swapChain->init(this->m_Hwnd, rc.right - rc.left, rc.bottom - rc.top);

	InputSystem::get()->addListener(this);

	void* shaderByteCode = nullptr;
	size_t byteCodeSize = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "main", &shaderByteCode, &byteCodeSize);
	vs = GraphicsEngine::get()->createVertexShader(shaderByteCode, byteCodeSize);

	DebugUtils::log("emplacing circle to vector");
	Circle* c = new Circle("circle", shaderByteCode, byteCodeSize, 0.5f);
	circleVector.push_back(c);

	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compileGeometryShader(L"GeometryShader.hlsl", "main", &shaderByteCode, &byteCodeSize);
	gs = GraphicsEngine::get()->createGeometryShader(shaderByteCode, byteCodeSize);
	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "main", &shaderByteCode, &byteCodeSize);
	ps = GraphicsEngine::get()->createPixelShader(shaderByteCode, byteCodeSize);
	GraphicsEngine::get()->releaseCompiledShader();

	// qList[0] = new Quad(
	// 	{ 1.0f, 1.0f },
	// 	{ -0.2f, 0.2f, 0.0f },
	// 	{ 0.5f, -0.8f, 0.0f },
	// 	{ 1.0f, 0.0f, 0.0f });
	//
	// cList[0] = new Cube();

	// qList[1] = new Quad(
	// 	{ 0.25f, 0.3f },
	// 	{ -0.5f, .2f },
	// 	{ -0.5f, .8f },
	// 	{ 0.0f, 1.0f, 0.0f });
	//
	// qList[2] = new Quad(
	// 	{ 0.25, 0.25 },
	// 	{ .2, -.5 },
	// 	{ .0f, -.8f },
	// 	{ 0, 0, 1 });
}

void AppWindow::onUpdate()
{

	Window::onUpdate();
	InputSystem::get()->update();

	ticks += EngineTime::getDeltaTime() * 1.0f;

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setGeometryShader(gs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(
		this->swapChain,
		0.15,
		0.2,
		0.60,
		1);

	const RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	/*for (Quad* q : qList)
	{
		q->draw(EngineTime::getDeltaTime(), getClientWindowRect());
	}*/

	/*for (Cube* c : cList)
	{
		c->draw(EngineTime::getDeltaTime(), getClientWindowRect());
	}*/

	//DebugUtils::log("update and draw circles");
	for (Circle* c : circleVector)
	{
		c->update(EngineTime::getDeltaTime());
		c->draw(vs, gs, ps, getClientWindowRect());
	}

	swapChain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	//vertexBuffer->release();
	swapChain->release();
	//vs->release();
	//ps->release();

	//GraphicsEngine::get()->release();
	GraphicsEngine::destroy();
}
