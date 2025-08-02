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
	Logger LogDefault = ::LimeEngine::LoggerManager::GetLogger();

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

	// LoggerManager

	LoggerManager::LoggerManager() noexcept
	{
		fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("Logs/LastOutputLog.log", true);
		sinks.emplace_back(fileSink);

		spdlog::set_level(spdlog::level::trace);
		spdlog::flush_on(spdlog::level::trace);
		spdlog::set_automatic_registration(true);
		spdlog::set_pattern("%^[%n][%Y.%m.%d %H:%M:%S %e][%l] %v%$");

		auto defaultLogger = CreateLogger("LogDefault");
		spdlog::set_default_logger(defaultLogger.nativeLogger);
	}

	LoggerManager* LoggerManager::GetLoggerManager() noexcept
	{
		static LoggerManager Instance;
		return &Instance;
	}

	Logger LoggerManager::CreateLogger(const std::string& category, LogLevel minLogLevel, LogLevel flushLogLevel) noexcept
	{
		auto nativeLogger = std::make_shared<spdlog::logger>(category, std::cbegin(sinks), std::cend(sinks));
		LE_ASSERT(nativeLogger);

		spdlog::initialize_logger(nativeLogger);
		loggers.emplace_back(nativeLogger);

		nativeLogger->set_level(static_cast<spdlog::level::level_enum>(minLogLevel));
		nativeLogger->flush_on(static_cast<spdlog::level::level_enum>(flushLogLevel));

		return Logger(std::move(nativeLogger));
	}

	Logger LoggerManager::GetLogger() noexcept
	{
		// Initialize LoggerManager
		GetLoggerManager();
		return Logger(spdlog::default_logger());
	}

	Logger LoggerManager::GetLogger(const std::string& category) noexcept
	{
		auto nativeLogger = spdlog::get(category);
		LE_ASSERT(nativeLogger);
		return Logger(std::move(nativeLogger));
	}

	std::optional<Logger> LoggerManager::TryGetLogger(const std::string& category) noexcept
	{
		auto nativeLogger = spdlog::get(category);
		if (!nativeLogger) { return std::nullopt; }
		return Logger(std::move(nativeLogger));
	}

	void LoggerManager::AddSink(const SRef<BaseLoggerSink>& sink)
	{
		sinks.emplace_back(sink);

		for (auto& logger : loggers)
		{
			logger->sinks().push_back(sink);
		}
	}

	void LoggerManager::RemoveSink(const SRef<BaseLoggerSink>& sink)
	{
		auto sinkIt = std::find(std::cbegin(sinks), std::cend(sinks), sink);
		sinks.erase(sinkIt);

		for (auto& logger : loggers)
		{
			auto loggerSinkIt = std::find(std::cbegin(logger->sinks()), std::cend(logger->sinks()), sink);
			logger->sinks().erase(loggerSinkIt);
		}
	}

	// Logger

	void Logger::Log(LogLevel level, std::string_view msg) const
	{
		nativeLogger->log(static_cast<spdlog::level::level_enum>(level), msg);
	}

	void Logger::AddSink(const SRef<BaseLoggerSink>& sink)
	{
		nativeLogger->sinks().push_back(sink);
	}

	void Logger::RemoveSink(const SRef<BaseLoggerSink>& sink)
	{
		auto& sinks = nativeLogger->sinks();
		auto sinkIt = std::find(std::begin(sinks), std::end(sinks), sink);
		if (sinkIt != std::end(sinks)) sinks.erase(sinkIt);
	}
}
