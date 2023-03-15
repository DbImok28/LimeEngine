// Copyright (C) 2022 Pavel Jakushik - All Rights Reserved
// See file LICENSE for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Window/Console.hpp"

// TODO: Remove dependencies
#include <spdlog/spdlog.h>

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
		bool CheckLogLevel(LogLevel level)
		{
			switch (level)
			{
#if defined(LE_LOG_NOTRACE)
				case LimeEngine::LogLevel::Trace: return false; break;
#elif defined(LE_LOG_WARNINGS_AND_ERRORS)
				case LimeEngine::LogLevel::Trace: return false; break;
				case LimeEngine::LogLevel::Info: return false; break;
#elif defined(LE_NOLOG)
				case LimeEngine::LogLevel::Trace: return false; break;
				case LimeEngine::LogLevel::Info: return false; break;
				case LimeEngine::LogLevel::Debug: return false; break;
				case LimeEngine::LogLevel::Warning: return false; break;
				case LimeEngine::LogLevel::Error: return false; break;
				case LimeEngine::LogLevel::CriticalError: return false; break;
#endif
				default: return true;
			}
		}
		void Log(LogLevel level, std::string_view msg) noexcept
		{
			if (CheckLogLevel(level)) spdLogger->log(static_cast<spdlog::level::level_enum>(level), msg);
		}
		template <typename... TArgs>
		void Log(LogLevel level, spdlog::format_string_t<TArgs...> fmsg, TArgs&&... args) noexcept
		{
			if (CheckLogLevel(level)) spdLogger->log(static_cast<spdlog::level::level_enum>(level), fmsg, std::forward<TArgs>(args)...);
		}

	private:
		std::shared_ptr<spdlog::logger> spdLogger;
	};
}

#ifdef _DEBUG
	#define LE_LOG_DEBUG(...)      ::LimeEngine::Logger::GetLogger().Log(::LimeEngine::LogLevel::Debug, __VA_ARGS__)
	#define LE_CORE_LOG_DEBUG(...) ::LimeEngine::Logger::GetCoreLogger().Log(::LimeEngine::LogLevel::Debug, __VA_ARGS__)
#else
	#define LE_LOG_DEBUG(...)      (void)0
	#define LE_CORE_LOG_DEBUG(...) (void)0
#endif

#if defined(LE_LOG_FULL)

	#define LE_LOG_LOG(...)            ::LimeEngine::Logger::GetLogger().Log(__VA_ARGS__)
	#define LE_LOG_TRACE(...)          ::LimeEngine::Logger::GetLogger().Log(::LimeEngine::LogLevel::Trace, __VA_ARGS__)
	#define LE_LOG_INFO(...)           ::LimeEngine::Logger::GetLogger().Log(::LimeEngine::LogLevel::Info, __VA_ARGS__)
	#define LE_LOG_WARNING(...)        ::LimeEngine::Logger::GetLogger().Log(::LimeEngine::LogLevel::Warning, __VA_ARGS__)
	#define LE_LOG_ERROR(...)          ::LimeEngine::Logger::GetLogger().Log(::LimeEngine::LogLevel::Error, __VA_ARGS__)
	#define LE_LOG_CRITICAL_ERROR(...) ::LimeEngine::Logger::GetLogger().Log(::LimeEngine::LogLevel::CriticalError, __VA_ARGS__)

	#define LE_CORE_LOG(...)                ::LimeEngine::Logger::GetCoreLogger().Log(__VA_ARGS__)
	#define LE_CORE_LOG_TRACE(...)          ::LimeEngine::Logger::GetCoreLogger().Log(::LimeEngine::LogLevel::Trace, __VA_ARGS__)
	#define LE_CORE_LOG_INFO(...)           ::LimeEngine::Logger::GetCoreLogger().Log(::LimeEngine::LogLevel::Info, __VA_ARGS__)
	#define LE_CORE_LOG_WARNING(...)        ::LimeEngine::Logger::GetCoreLogger().Log(::LimeEngine::LogLevel::Warning, __VA_ARGS__)
	#define LE_CORE_LOG_ERROR(...)          ::LimeEngine::Logger::GetCoreLogger().Log(::LimeEngine::LogLevel::Error, __VA_ARGS__)
	#define LE_CORE_LOG_CRITICAL_ERROR(...) ::LimeEngine::Logger::GetCoreLogger().Log(::LimeEngine::LogLevel::CriticalError, __VA_ARGS__)

#elif defined(LE_LOG_NOTRACE)

	#define LE_LOG_LOG(...)            ::LimeEngine::Logger::GetLogger().Log(__VA_ARGS__)
	#define LE_LOG_TRACE(...)          (void)0
	#define LE_LOG_INFO(...)           ::LimeEngine::Logger::GetLogger().Log(::LimeEngine::LogLevel::Info, __VA_ARGS__)
	#define LE_LOG_WARNING(...)        ::LimeEngine::Logger::GetLogger().Log(::LimeEngine::LogLevel::Warning, __VA_ARGS__)
	#define LE_LOG_ERROR(...)          ::LimeEngine::Logger::GetLogger().Log(::LimeEngine::LogLevel::Error, __VA_ARGS__)
	#define LE_LOG_CRITICAL_ERROR(...) ::LimeEngine::Logger::GetLogger().Log(::LimeEngine::LogLevel::CriticalError, __VA_ARGS__)

	#define LE_CORE_LOG(...)                ::LimeEngine::Logger::GetCoreLogger().Log(__VA_ARGS__)
	#define LE_CORE_LOG_TRACE(...)          (void)0
	#define LE_CORE_LOG_INFO(...)           ::LimeEngine::Logger::GetCoreLogger().Log(::LimeEngine::LogLevel::Info, __VA_ARGS__)
	#define LE_CORE_LOG_WARNING(...)        ::LimeEngine::Logger::GetCoreLogger().Log(::LimeEngine::LogLevel::Warning, __VA_ARGS__)
	#define LE_CORE_LOG_ERROR(...)          ::LimeEngine::Logger::GetCoreLogger().Log(::LimeEngine::LogLevel::Error, __VA_ARGS__)
	#define LE_CORE_LOG_CRITICAL_ERROR(...) ::LimeEngine::Logger::GetCoreLogger().Log(::LimeEngine::LogLevel::CriticalError, __VA_ARGS__)

#elif defined(LE_LOG_WARNINGS_AND_ERRORS)

	#define LE_LOG_LOG(...)            ::LimeEngine::Logger::GetLogger().Log(__VA_ARGS__)
	#define LE_LOG_TRACE(...)          (void)0
	#define LE_LOG_INFO(...)           (void)0
	#define LE_LOG_WARNING(...)        ::LimeEngine::Logger::GetLogger().Log(::LimeEngine::LogLevel::Warning, __VA_ARGS__)
	#define LE_LOG_ERROR(...)          ::LimeEngine::Logger::GetLogger().Log(::LimeEngine::LogLevel::Error, __VA_ARGS__)
	#define LE_LOG_CRITICAL_ERROR(...) ::LimeEngine::Logger::GetLogger().Log(::LimeEngine::LogLevel::CriticalError, __VA_ARGS__)

	#define LE_CORE_LOG(...)                ::LimeEngine::Logger::GetCoreLogger().Log(__VA_ARGS__)
	#define LE_CORE_LOG_TRACE(...)          (void)0
	#define LE_CORE_LOG_INFO(...)           (void)0
	#define LE_CORE_LOG_WARNING(...)        ::LimeEngine::Logger::GetCoreLogger().Log(::LimeEngine::LogLevel::Warning, __VA_ARGS__)
	#define LE_CORE_LOG_ERROR(...)          ::LimeEngine::Logger::GetCoreLogger().Log(::LimeEngine::LogLevel::Error, __VA_ARGS__)
	#define LE_CORE_LOG_CRITICAL_ERROR(...) ::LimeEngine::Logger::GetCoreLogger().Log(::LimeEngine::LogLevel::CriticalError, __VA_ARGS__)

#elif defined(LE_NOLOG)

	#define LE_LOG_LOG(...)            (void)0
	#define LE_LOG_TRACE(...)          (void)0
	#define LE_LOG_INFO(...)           (void)0
	#define LE_LOG_WARNING(...)        (void)0
	#define LE_LOG_ERROR(...)          (void)0
	#define LE_LOG_CRITICAL_ERROR(...) (void)0

	#define LE_CORE_LOG(...)                (void)0
	#define LE_CORE_LOG_TRACE(...)          (void)0
	#define LE_CORE_LOG_INFO(...)           (void)0
	#define LE_CORE_LOG_WARNING(...)        (void)0
	#define LE_CORE_LOG_ERROR(...)          (void)0
	#define LE_CORE_LOG_CRITICAL_ERROR(...) (void)0

#endif