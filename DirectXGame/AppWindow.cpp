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
		circleVector.emplace_back();
		break;
	}
	case VK_ESCAPE:
		exit(0);
		break;
	case VK_DELETE:
		circleVector.clear();
		break;
	case VK_BACK:
	{
		if (!circleVector.empty())
			circleVector.pop_back();
		break;
	}
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

	qList[0] = new Quad(
		{ 1.0f, 1.0f },
		{ -0.2f, 0.2f, 0.0f },
		{ 0.5f, -0.8f, 0.0f },
		{ 1.0f, 0.0f, 0.0f });

	cList[0] = new Cube();

	circleVector.push_back(Circle({0.1f, 0.1f}, {0.5f, 0.5f, 0.0f}));

	/*
	int n = 10; // number of triangles
	SimpleVertex* vertices = malloc(sizeof(SimpleVertex) * 10 * 3); // 10 triangles, 3 verticies per triangle
	float deltaTheta = 2*pi / n; // Change in theta for each vertex
	for( int i = 0; i < n; i++ ) {
		int theta = i * deltaTheta; // Theta is the angle for that triangle
		int index = 3 * i;
		vertices[index + 0] = SimpleVertex(0, 0, 0);
		// Given an angle theta, cosine [cos] will give you the x coordinate,
		// and sine [sin] will give you the y coordinate.
		// #include <math.h>
		vertices[index + 1] = SimpleVertex(cos(theta), sin(theta), 0);
		vertices[index + 2] = SimpleVertex(cos(theta + deltaTheta), sin(theta + deltaTheta), 0);
	}
	*/

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

	for (Circle c : circleVector)
	{
		c.draw(EngineTime::getDeltaTime(), getClientWindowRect());
	}

	swapChain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	//vb->release();
	swapChain->release();
	//vs->release();
	//ps->release();

	//GraphicsEngine::get()->release();
	GraphicsEngine::destroy();
}

void AppWindow::updateQuadPosition()
{

}
