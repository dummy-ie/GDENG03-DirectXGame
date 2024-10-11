#pragma once
#include <string>
#include <iostream>

class DebugUtils
{
public:
	static void debugLog(const std::string& msg)
	{
		std::cout << "[DEBUG]: " << msg << std::endl;
	}
	
};
