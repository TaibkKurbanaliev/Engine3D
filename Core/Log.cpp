#include "Log.h"
#include <iostream>
#include <format>

namespace Engine
{
	void Log::Init()
	{

	}

	void Log::PrintMessage(WarningLevel warningLevel, std::string fmt)
	{
		const int WHITE = 7;
		SetColor(warningLevel);
		std::cout << fmt << std::endl;
		SetColor(WHITE);
	}

	void Log::SetColor(int text)
	{
		std::cout << std::format("\033[1;3{}m", text);
	}
}