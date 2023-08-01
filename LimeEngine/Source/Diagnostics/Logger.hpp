// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Window/Console.hpp"

// TODO: Remove dependencies
#define SPDLOG_USE_STD_FORMAT
#include <spdlog/spdlog.h>

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
	enum class LogLevel
	{
		Trace = SPDLOG_LEVEL_TRACE,
		Debug = SPDLOG_LEVEL_DEBUG,
		Info = SPDLOG_LEVEL_INFO,
		Warning = SPDLOG_LEVEL_WARN,
		Error = SPDLOG_LEVEL_ERROR,
		CriticalError = SPDLOG_LEVEL_CRITICAL,
	};

	class LE_API Logger
	{
	public:
		inline static Logger GetCoreLogger() noexcept
		{
			return coreLogger;
		}
		inline static Logger GetLogger() noexcept
		{
			return appLogger;
		}
		static void StaticInitialize();
		LE_STATIC_INITIALIZE(StaticInitialize, std::numeric_limits<int8>::max());

	private:
		static Logger coreLogger;
		static Logger appLogger;

	public:
		Logger() = default;
		Logger(const Logger&) = default;
		Logger(Logger&&) noexcept = default;
		Logger& operator=(const Logger&) = default;
		Logger& operator=(Logger&&) noexcept = default;

		void Initialize(const std::string& name);
		bool CheckLogLevel(LogLevel level) const noexcept
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
		void Log(LogLevel level, std::string_view msg) const
		{
			if (CheckLogLevel(level)) spdLogger->log(static_cast<spdlog::level::level_enum>(level), msg);
		}
		template <typename... TArgs>
		void Log(LogLevel level, std::format_string<TArgs...> formatMsg, TArgs&&... args) const
		{
			if (CheckLogLevel(level)) spdLogger->log(static_cast<spdlog::level::level_enum>(level), formatMsg, std::forward<TArgs>(args)...);
		}

	private:
		std::shared_ptr<spdlog::logger> spdLogger;
	};
}

#define LE_LOG_LOG(logLevel, ...)  ::LimeEngine::Logger::GetLogger().Log(logLevel, __VA_ARGS__)
#define LE_CORE_LOG(logLevel, ...) ::LimeEngine::Logger::GetCoreLogger().Log(logLevel, __VA_ARGS__)

#ifdef _DEBUG
	#define LE_LOG_DEBUG(...)      ::LimeEngine::Logger::GetLogger().Log(::LimeEngine::LogLevel::Debug, __VA_ARGS__)
	#define LE_CORE_LOG_DEBUG(...) ::LimeEngine::Logger::GetCoreLogger().Log(::LimeEngine::LogLevel::Debug, __VA_ARGS__)
#else
	#define LE_LOG_DEBUG(...)      (void)0
	#define LE_CORE_LOG_DEBUG(...) (void)0
#endif

#if defined(LE_ENABLE_LOG_TRACE)
	#define LE_LOG_TRACE(...)      ::LimeEngine::Logger::GetLogger().Log(::LimeEngine::LogLevel::Trace, __VA_ARGS__)
	#define LE_CORE_LOG_TRACE(...) ::LimeEngine::Logger::GetCoreLogger().Log(::LimeEngine::LogLevel::Trace, __VA_ARGS__)
#else
	#define LE_LOG_TRACE(...)      (void)0
	#define LE_CORE_LOG_TRACE(...) (void)0
#endif

#if defined(LE_ENABLE_LOG_INFO)
	#define LE_LOG_INFO(...)      ::LimeEngine::Logger::GetLogger().Log(::LimeEngine::LogLevel::Info, __VA_ARGS__)
	#define LE_CORE_LOG_INFO(...) ::LimeEngine::Logger::GetCoreLogger().Log(::LimeEngine::LogLevel::Info, __VA_ARGS__)
#else
	#define LE_LOG_INFO(...)      (void)0
	#define LE_CORE_LOG_INFO(...) (void)0
#endif

#if defined(LE_ENABLE_LOG_WARNING)
	#define LE_LOG_WARNING(...)      ::LimeEngine::Logger::GetLogger().Log(::LimeEngine::LogLevel::Warning, __VA_ARGS__)
	#define LE_CORE_LOG_WARNING(...) ::LimeEngine::Logger::GetCoreLogger().Log(::LimeEngine::LogLevel::Warning, __VA_ARGS__)
#else
	#define LE_LOG_WARNING(...)      (void)0
	#define LE_CORE_LOG_WARNING(...) (void)0
#endif

#if defined(LE_ENABLE_LOG_ERROR)
	#define LE_LOG_ERROR(...)      ::LimeEngine::Logger::GetLogger().Log(::LimeEngine::LogLevel::Error, __VA_ARGS__)
	#define LE_CORE_LOG_ERROR(...) ::LimeEngine::Logger::GetCoreLogger().Log(::LimeEngine::LogLevel::Error, __VA_ARGS__)
#else
	#define LE_LOG_ERROR(...)      (void)0
	#define LE_CORE_LOG_ERROR(...) (void)0
#endif

#if defined(LE_ENABLE_LOG_CRITICAL_ERROR)
	#define LE_LOG_CRITICAL_ERROR(...)      ::LimeEngine::Logger::GetLogger().Log(::LimeEngine::LogLevel::CriticalError, __VA_ARGS__)
	#define LE_CORE_LOG_CRITICAL_ERROR(...) ::LimeEngine::Logger::GetCoreLogger().Log(::LimeEngine::LogLevel::CriticalError, __VA_ARGS__)
#else
	#define LE_LOG_CRITICAL_ERROR(...)      (void)0
	#define LE_CORE_LOG_CRITICAL_ERROR(...) (void)0
#endif
