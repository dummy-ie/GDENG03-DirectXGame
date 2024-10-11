#include "Window.h"

//Window* window = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		// Event fired when window is created
		// collected here...
		Window* window = static_cast<Window*>(reinterpret_cast<LPCREATESTRUCT>(lparam)->lpCreateParams);
		// ...and then stored for later lookup
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		window->setHwnd(hwnd);
		window->onCreate();
		break;
	}
	case WM_DESTROY:
	{
		// Event fired when window is destroyed
		Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		window->onDestroy();
		::PostQuitMessage(0);
		break;
	}
	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}

bool Window::init()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = nullptr;
	wc.lpszClassName = "MyWindowClass";
	wc.lpszMenuName = "";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc))
		return false;

	m_Hwnd = ::CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		"MyWindowClass",
		"[LEOCARIO] DirectX Application",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1024,
		768,
		nullptr,
		nullptr,
		nullptr,
		this);

	if (!m_Hwnd)
		return false;

	::ShowWindow(m_Hwnd, SW_SHOW);
	::UpdateWindow(m_Hwnd);

	EngineTime::initialize();

	m_IsRunning = true;

	return true;
}

bool Window::broadcast()
{
	MSG msg;

	EngineTime::logFrameStart();
	this->onUpdate();

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(1);
	EngineTime::logFrameEnd();

	return true;
}

bool Window::release()
{
	if (!::DestroyWindow(m_Hwnd))
		return false;

	return true;
}

bool Window::isRunning()
{
	return m_IsRunning;
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_Hwnd, &rc);
	return rc;
}

void Window::setHwnd(HWND hwnd)
{
	this->m_Hwnd = hwnd;
}

void Window::onCreate()
{

}

void Window::onUpdate()
{

}

void Window::onDestroy()
{
	m_IsRunning = false;
}
