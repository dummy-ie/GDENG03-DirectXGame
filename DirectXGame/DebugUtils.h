#pragma once
#include <string>
#include <iostream>

class DebugUtils
{
public:
	static void log(const std::string& msg)
	{
		std::cout << "[DEBUG]: " << msg << '\n';
	}

	static void error(const std::string& msg)
	{
		std::cout << "[ERROR]: " << msg << '\n';
	}
	
};
