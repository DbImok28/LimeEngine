// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
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
#ifdef LE_ENABLE_CONSOLE
		sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
#endif
		sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Logs/LastOutputLog.log", true));
		spdLogger = std::make_shared<spdlog::logger>(name, sinks.begin(), sinks.end());
		spdLogger->set_level(spdlog::level::trace);
		spdLogger->flush_on(spdlog::level::trace);
		spdLogger->set_pattern("%^[%n][%Y.%m.%d %H:%M:%S %e][%l] %v%$");
		spdlog::register_logger(spdLogger);
	}

	bool Logger::CheckLogLevel(LogLevel level) const noexcept
	{
		switch (level)
		{
			case LimeEngine::LogLevel::Debug: return true; break;
#if defined(LE_ENABLE_LOG_TRACE)
			case LimeEngine::LogLevel::Trace: return true; break;
#endif
#if defined(LE_ENABLE_LOG_INFO)
			case LimeEngine::LogLevel::Info: return true; break;
#endif
#if defined(LE_ENABLE_LOG_WARNING)
			case LimeEngine::LogLevel::Warning: return true; break;
#endif
#if defined(LE_ENABLE_LOG_ERROR)
			case LimeEngine::LogLevel::Error: return true; break;
#endif
#if defined(LE_ENABLE_LOG_CRITICAL_ERROR)
			case LimeEngine::LogLevel::CriticalError: return true; break;
#endif
			default: return false;
		}
	}

	void Logger::Log(LogLevel level, std::string_view msg) const
	{
		if (CheckLogLevel(level)) spdLogger->log(static_cast<spdlog::level::level_enum>(level), msg);
	}
}