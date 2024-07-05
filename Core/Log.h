#pragma once
#include <string>

namespace Engine
{
	enum WarningLevel
	{
		OK = 2,
		INFO = 4,
		WARNING = 3,
		FATAL = 1
	};

	class Log
	{
	public:
		static void Init();
		static void PrintMessage(WarningLevel warningLevel, std::string fmt);
	private:
		static void SetColor(int text);
	};
}

#ifdef _DEBUG
#define ENGINE_CORE_FATAL(message) ::Engine::Log::PrintMessage(::Engine::WarningLevel::FATAL, message)
#define ENGINE_CORE_WARN(message) ::Engine::Log::PrintMessage(::Engine::WarningLevel::WARNING, message)
#define ENGINE_CORE_INFO(message) ::Engine::Log::PrintMessage(::Engine::WarningLevel::INFO, message)
#define ENGINE_CORE_OK(message) ::Engine::Log::PrintMessage(::Engine::WarningLevel::OK, message)
#else
#define ENGINE_CORE_FATAL(message) 
#define ENGINE_CORE_WARN(message) 
#define ENGINE_CORE_INFO(message) 
#define ENGINE_CORE_OK(message) 
#endif // DEBUG
