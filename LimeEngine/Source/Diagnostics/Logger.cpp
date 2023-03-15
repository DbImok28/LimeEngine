#include "lepch.hpp"
#include "Logger.hpp"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace LimeEngine
{
	Logger Logger::coreLogger{};
	Logger Logger::appLogger{};

	void Logger::StaticInitialize()
	{
		coreLogger.Initialize("Engine");
		appLogger.Initialize("App");
	}

	void Logger::Initialize(const std::string& name)
	{
		std::vector<spdlog::sink_ptr> sinks;
#ifdef LE_CONSOLE
		sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
#endif
		sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Logs/LastOutputLog.log", true));
		spdLogger = std::make_shared<spdlog::logger>(name, sinks.begin(), sinks.end());
		spdLogger->set_level(spdlog::level::trace);
		spdLogger->flush_on(spdlog::level::trace);
		spdLogger->set_pattern("%^[%n][%Y.%m.%d %H:%M:%S %e][%l] %v%$");
		spdlog::register_logger(spdLogger);
	}
}