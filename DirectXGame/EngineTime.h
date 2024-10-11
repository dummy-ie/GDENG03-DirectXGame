#pragma once
#include <ctime>
#include <chrono>
#include <iostream>

class Window;

class EngineTime
{
public:
	static void initialize();
	static double getDeltaTime();

private:
	EngineTime();
	~EngineTime();
	EngineTime(EngineTime const&) {};
	EngineTime& operator=(EngineTime const&) {};
	static EngineTime* sharedInstance;

	static void logFrameStart();
	static void logFrameEnd();

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	double deltaTime = 0.0;

	friend class Window;
};

