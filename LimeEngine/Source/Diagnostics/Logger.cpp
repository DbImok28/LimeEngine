// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Logger.hpp"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "Diagnostics/LoggerSink.hpp"

namespace LimeEngine
{
	Vector4D LogLevelToColor(LogLevel logLevel) noexcept
	{
		switch (logLevel)
		{
			case LogLevel::Trace: return { 0.5f, 0.5f, 0.5f, 1.0f };
			case LogLevel::Debug: return { 0.0f, 1.0f, 0.0f, 1.0f };
			case LogLevel::Info: return { 1.0f, 1.0f, 1.0f, 1.0f };
			case LogLevel::Warning: return { 1.0f, 1.0f, 0.0f, 1.0f };
			case LogLevel::Error: return { 1.0f, 0.0f, 0.0f, 1.0f };
			case LogLevel::CriticalError: return { 1.0f, 0.0f, 0.0f, 1.0f };
			default: return { 1.0f, 0.0f, 0.0f, 1.0f };
		}
	}

	Logger::Logger(const std::string& name)
	{
		Initialize(name);
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

	bool Logger::CheckLogLevel(LogLevel level) noexcept
	{
		switch (level)
		{
			case LogLevel::Debug: return true;
#if defined(LE_ENABLE_LOG_TRACE)
			case LogLevel::Trace: return true;
#endif
#if defined(LE_ENABLE_LOG_INFO)
			case LogLevel::Info: return true;
#endif
#if defined(LE_ENABLE_LOG_WARNING)
			case LogLevel::Warning: return true;
#endif
#if defined(LE_ENABLE_LOG_ERROR)
			case LogLevel::Error: return true;
#endif
#if defined(LE_ENABLE_LOG_CRITICAL_ERROR)
			case LogLevel::CriticalError: return true;
#endif
			default: return false;
		}
	}

	void Logger::Log(LogLevel level, std::string_view msg) const
	{
		if (CheckLogLevel(level)) spdLogger->log(static_cast<spdlog::level::level_enum>(level), msg);
	}

	SRef<spdlog::logger> Logger::GetNativeLogger() noexcept
	{
		return spdLogger;
	}

	void Logger::AddSink(const SRef<LoggerSink>& sink)
	{
		spdLogger->sinks().push_back(sink);
	}

	void Logger::RemoveSink(const SRef<LoggerSink>& sink)
	{
		auto& sinks = spdLogger->sinks();
		auto sinkIt = std::find(std::begin(sinks), std::end(sinks), sink);
		if (sinkIt != std::end(sinks)) sinks.erase(sinkIt);
	}
}
