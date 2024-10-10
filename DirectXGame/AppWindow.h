#pragma once

#include <Windows.h>
#include <vector>
#include <iostream>

#include "Window.h"
#include "EngineTime.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "Cube.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"
#include "Quad.h"
#include "Circle.h"
#include "MathUtil.h"

class AppWindow final : public Window, public InputListener
{
public:
	static AppWindow* get();
	static void initialize();
	static void destroy();

	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;

	void updateQuadPosition();

private:
	AppWindow();
	~AppWindow();
	AppWindow(AppWindow const&) {};
	AppWindow& operator=(AppWindow const&) {};
	static AppWindow* sharedInstance;

	Quad* qList[1]; // object manager later
	Cube* cList[1]; // object manager later
	std::vector<Circle> circleVector;

	SwapChain* swapChain;

	VertexBuffer* vb;
	ConstantBuffer* cb;

	VertexShader* vs;
	PixelShader* ps;

	float ticks = 0.0f;

	// Inherited via InputListener
	void onKeyDown(int key) override;
	void onKeyUp(int key) override;
};

