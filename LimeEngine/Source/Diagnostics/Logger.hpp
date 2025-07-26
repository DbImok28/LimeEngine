// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Base/Vector.hpp"

// TODO: Remove dependencies
#define SPDLOG_USE_STD_FORMAT
#define SPDLOG_DISABLE_DEFAULT_LOGGER
#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>

#include <utility>

namespace LimeEngine
{
#define LE_DECLARE_EXTERN_LOGGER(category)   extern ::LimeEngine::Logger category
#define LE_DEFINE_LOGGER(category)           ::LimeEngine::Logger category = ::LimeEngine::LoggerManager::GetLoggerManager()->CreateLogger(#category)

#define LE_LOG(category, level, ...)         ::LimeEngine::LoggerManager::GetLogger(category).Log(level, __VA_ARGS__)
#define LE_LOG_DEBUG(category, ...)          LE_LOG(category, ::LimeEngine::LogLevel::Debug, __VA_ARGS__)
#define LE_LOG_TRACE(category, ...)          LE_LOG(category, ::LimeEngine::LogLevel::Trace, __VA_ARGS__)
#define LE_LOG_INFO(category, ...)           LE_LOG(category, ::LimeEngine::LogLevel::Info, __VA_ARGS__)
#define LE_LOG_WARNING(category, ...)        LE_LOG(category, ::LimeEngine::LogLevel::Warning, __VA_ARGS__)
#define LE_LOG_ERROR(category, ...)          LE_LOG(category, ::LimeEngine::LogLevel::Error, __VA_ARGS__)
#define LE_LOG_CRITICAL_ERROR(category, ...) LE_LOG(category, ::LimeEngine::LogLevel::CriticalError, __VA_ARGS__)

	using BaseLoggerSink = spdlog::sinks::sink;

	class Logger;
	LE_DECLARE_EXTERN_LOGGER(LogDefault);

	enum class LogLevel
	{
		Trace = SPDLOG_LEVEL_TRACE,
		Debug = SPDLOG_LEVEL_DEBUG,
		Info = SPDLOG_LEVEL_INFO,
		Warning = SPDLOG_LEVEL_WARN,
		Error = SPDLOG_LEVEL_ERROR,
		CriticalError = SPDLOG_LEVEL_CRITICAL,
	};

	// TODO: Replace Vector4D to Color
	Vector4D LogLevelToColor(LogLevel logLevel) noexcept;

	class LE_API LoggerManager
	{
	private:
		LoggerManager() noexcept;

	public:
		// TODO: Add multithreaded logger support
		static LoggerManager* GetLoggerManager() noexcept;

		static Logger GetLogger() noexcept;
		static Logger GetLogger(const std::string& category) noexcept;
		inline static const Logger& GetLogger(const Logger& logger) noexcept
		{
			return logger;
		}
		static std::optional<Logger> TryGetLogger(const std::string& category) noexcept;

		Logger CreateLogger(const std::string& category, LogLevel minLogLevel = LogLevel::Trace, LogLevel flushLogLevel = LogLevel::Trace) noexcept;

	public:
		void AddSink(const SRef<BaseLoggerSink>& sink);
		void RemoveSink(const SRef<BaseLoggerSink>& sink);

	private:
		SRef<BaseLoggerSink> fileSink;
		std::vector<SRef<BaseLoggerSink>> sinks;
		std::vector<SRef<spdlog::logger>> loggers;
	};

	class LE_API Logger
	{
		friend LoggerManager;

	private:
		explicit Logger(SRef<spdlog::logger>&& nativeLogger) : nativeLogger(std::move(nativeLogger)) {}

	public:
		template <typename... TArgs>
		void Log(LogLevel level, std::format_string<TArgs...> formatMsg, TArgs&&... args) const
		{
			nativeLogger->log(static_cast<spdlog::level::level_enum>(level), formatMsg, std::forward<TArgs>(args)...);
		}
		void Log(LogLevel level, std::string_view msg) const;

		void AddSink(const SRef<BaseLoggerSink>& sink);
		void RemoveSink(const SRef<BaseLoggerSink>& sink);

	private:
		SRef<spdlog::logger> nativeLogger;
	};
}
