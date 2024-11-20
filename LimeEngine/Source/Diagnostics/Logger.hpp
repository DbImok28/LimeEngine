// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Window/Console.hpp"
#include "Base/Vector.hpp"

// TODO: Remove dependencies
#define SPDLOG_USE_STD_FORMAT
#include <spdlog/spdlog.h>

#include <spdlog/sinks/base_sink.h>

#if defined(LE_LOG_PRESET_FULL)
	#define LE_ENABLE_LOG_TRACE
	#define LE_ENABLE_LOG_INFO
	#define LE_ENABLE_LOG_WARNING
	#define LE_ENABLE_LOG_ERROR
	#define LE_ENABLE_LOG_CRITICAL_ERROR
#endif
#if defined(LE_LOG_PRESET_FULL_NOTRACE)
	#define LE_ENABLE_LOG_INFO
	#define LE_ENABLE_LOG_WARNING
	#define LE_ENABLE_LOG_ERROR
	#define LE_ENABLE_LOG_CRITICAL_ERROR
#endif
#if defined(LE_LOG_PRESET_WARNINGS_AND_ERRORS)
	#define LE_ENABLE_LOG_WARNING
	#define LE_ENABLE_LOG_ERROR
	#define LE_ENABLE_LOG_CRITICAL_ERROR
#endif

namespace LimeEngine
{
	class OutputLogPanel;

	enum class LogLevel
	{
		Trace = SPDLOG_LEVEL_TRACE,
		Debug = SPDLOG_LEVEL_DEBUG,
		Info = SPDLOG_LEVEL_INFO,
		Warning = SPDLOG_LEVEL_WARN,
		Error = SPDLOG_LEVEL_ERROR,
		CriticalError = SPDLOG_LEVEL_CRITICAL,
	};

	Vector4D LogLevelToColor(LogLevel logLevel) noexcept;

	class LoggerSink;

	class LE_API Logger
	{
	public:
		inline static Logger* GetCoreLogger() noexcept
		{
			return &coreLogger;
		}
		inline static Logger* GetLogger() noexcept
		{
			return &appLogger;
		}

	private:
		static Logger coreLogger;
		static Logger appLogger;

	public:
		explicit Logger(const std::string& name);
		LE_DEFAULT_MOVE_COPY(Logger)

		void Initialize(const std::string& name);

		static bool CheckLogLevel(LogLevel level) noexcept;

		void Log(LogLevel level, std::string_view msg) const;
		template <typename... TArgs>
		void Log(LogLevel level, std::format_string<TArgs...> formatMsg, TArgs&&... args) const
		{
			if (CheckLogLevel(level)) spdLogger->log(static_cast<spdlog::level::level_enum>(level), formatMsg, std::forward<TArgs>(args)...);
		}

		void AddSink(const SRef<LoggerSink>& sink);
		void RemoveSink(const SRef<LoggerSink>& sink);

		SRef<spdlog::logger> GetNativeLogger() noexcept;

	private:
		SRef<spdlog::logger> spdLogger;
	};
}

#define LE_LOG(logLevel, ...)      ::LimeEngine::Logger::GetLogger()->Log(logLevel, __VA_ARGS__)
#define LE_CORE_LOG(logLevel, ...) ::LimeEngine::Logger::GetCoreLogger()->Log(logLevel, __VA_ARGS__)

#ifdef _DEBUG
	#define LE_LOG_DEBUG(...)      LE_LOG(::LimeEngine::LogLevel::Debug, __VA_ARGS__)
	#define LE_CORE_LOG_DEBUG(...) LE_CORE_LOG(::LimeEngine::LogLevel::Debug, __VA_ARGS__)
#else
	#define LE_LOG_DEBUG(...)      LE_REQUIRE_SEMICOLON
	#define LE_CORE_LOG_DEBUG(...) LE_REQUIRE_SEMICOLON
#endif

#if defined(LE_ENABLE_LOG_TRACE)
	#define LE_LOG_TRACE(...)      LE_LOG(::LimeEngine::LogLevel::Trace, __VA_ARGS__)
	#define LE_CORE_LOG_TRACE(...) LE_CORE_LOG(::LimeEngine::LogLevel::Trace, __VA_ARGS__)
#else
	#define LE_LOG_TRACE(...)      LE_REQUIRE_SEMICOLON
	#define LE_CORE_LOG_TRACE(...) LE_REQUIRE_SEMICOLON
#endif

#if defined(LE_ENABLE_LOG_INFO)
	#define LE_LOG_INFO(...)      LE_LOG(::LimeEngine::LogLevel::Info, __VA_ARGS__)
	#define LE_CORE_LOG_INFO(...) LE_CORE_LOG(::LimeEngine::LogLevel::Info, __VA_ARGS__)
#else
	#define LE_LOG_INFO(...)      LE_REQUIRE_SEMICOLON
	#define LE_CORE_LOG_INFO(...) LE_REQUIRE_SEMICOLON
#endif

#if defined(LE_ENABLE_LOG_WARNING)
	#define LE_LOG_WARNING(...)      LE_LOG(::LimeEngine::LogLevel::Warning, __VA_ARGS__)
	#define LE_CORE_LOG_WARNING(...) LE_CORE_LOG(::LimeEngine::LogLevel::Warning, __VA_ARGS__)
#else
	#define LE_LOG_WARNING(...)      LE_REQUIRE_SEMICOLON
	#define LE_CORE_LOG_WARNING(...) LE_REQUIRE_SEMICOLON
#endif

#if defined(LE_ENABLE_LOG_ERROR)
	#define LE_LOG_ERROR(...)      LE_LOG(::LimeEngine::LogLevel::Error, __VA_ARGS__)
	#define LE_CORE_LOG_ERROR(...) LE_CORE_LOG(::LimeEngine::LogLevel::Error, __VA_ARGS__)
#else
	#define LE_LOG_ERROR(...)      LE_REQUIRE_SEMICOLON
	#define LE_CORE_LOG_ERROR(...) LE_REQUIRE_SEMICOLON
#endif

#if defined(LE_ENABLE_LOG_CRITICAL_ERROR)
	#define LE_LOG_CRITICAL_ERROR(...)      LE_LOG(::LimeEngine::LogLevel::CriticalError, __VA_ARGS__)
	#define LE_CORE_LOG_CRITICAL_ERROR(...) LE_CORE_LOG(::LimeEngine::LogLevel::CriticalError, __VA_ARGS__)
#else
	#define LE_LOG_CRITICAL_ERROR(...)      LE_REQUIRE_SEMICOLON
	#define LE_CORE_LOG_CRITICAL_ERROR(...) LE_REQUIRE_SEMICOLON
#endif
