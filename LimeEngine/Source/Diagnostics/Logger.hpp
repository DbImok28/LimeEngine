// Copyright (C) 2022 Pavel Jakushik - All Rights Reserved
// See file LICENSE for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"

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
			return coreLoger;
		}
		inline static Logger GetLogger() noexcept
		{
			return appLoger;
		}
		static void Initialize();

	private:
		static Logger coreLoger;
		static Logger appLoger;

	public:
		explicit Logger(const std::string& name);
		Logger(const Logger&) = default;
		Logger(Logger&&) noexcept = default;
		Logger& operator=(const Logger&) = default;
		Logger& operator=(Logger&&) noexcept = default;

		void Log(LogLevel level, std::string_view msg) noexcept
		{
			spdLogger->log(static_cast<spdlog::level::level_enum>(level), msg);
		}
		template <typename... TArgs>
		void Log(LogLevel level, spdlog::format_string_t<TArgs...> fmsg, TArgs&&... args) noexcept
		{
			spdLogger->log(static_cast<spdlog::level::level_enum>(level), fmsg, std::forward<TArgs>(args)...);
		}

	private:
		std::shared_ptr<spdlog::logger> spdLogger;
	};
}

#ifdef _DEBUG
	#define LE_DEBUG(...)      ::LimeEngine::Logger::GetLogger().Log(LogLevel::Debug, __VA_ARGS__)
	#define LE_CORE_DEBUG(...) ::LimeEngine::Logger::GetCoreLogger().Log(LogLevel::Debug, __VA_ARGS__)
#else
	#define LE_DEBUG(...)      (void)0
	#define LE_CORE_DEBUG(...) (void)0
#endif

#if defined(LE_LOG_FULL)

	#define LE_LOG(...)            ::LimeEngine::Logger::GetLogger().Log(__VA_ARGS__)
	#define LE_TRACE(...)          ::LimeEngine::Logger::GetLogger().Log(LogLevel::Trace, __VA_ARGS__)
	#define LE_INFO(...)           ::LimeEngine::Logger::GetLogger().Log(LogLevel::Info, __VA_ARGS__)
	#define LE_WARNING(...)        ::LimeEngine::Logger::GetLogger().Log(LogLevel::Warning, __VA_ARGS__)
	#define LE_ERROR(...)          ::LimeEngine::Logger::GetLogger().Log(LogLevel::Error, __VA_ARGS__)
	#define LE_CRITICAL_ERROR(...) ::LimeEngine::Logger::GetLogger().Log(LogLevel::CriticalError, __VA_ARGS__)

	#define LE_CORE(...)                ::LimeEngine::Logger::GetCoreLogger().Log(__VA_ARGS__)
	#define LE_CORE_TRACE(...)          ::LimeEngine::Logger::GetCoreLogger().Log(LogLevel::Trace, __VA_ARGS__)
	#define LE_CORE_INFO(...)           ::LimeEngine::Logger::GetCoreLogger().Log(LogLevel::Info, __VA_ARGS__)
	#define LE_CORE_WARNING(...)        ::LimeEngine::Logger::GetCoreLogger().Log(LogLevel::Warning, __VA_ARGS__)
	#define LE_CORE_ERROR(...)          ::LimeEngine::Logger::GetCoreLogger().Log(LogLevel::Error, __VA_ARGS__)
	#define LE_CORE_CRITICAL_ERROR(...) ::LimeEngine::Logger::GetCoreLogger().Log(LogLevel::CriticalError, __VA_ARGS__)

#elif defined(LE_LOG_NOTRACE)

	#define LE_LOG(...)            ::LimeEngine::Logger::GetLogger().Log(__VA_ARGS__)
	#define LE_TRACE(...)          (void)0
	#define LE_INFO(...)           ::LimeEngine::Logger::GetLogger().Log(LogLevel::Info, __VA_ARGS__)
	#define LE_WARNING(...)        ::LimeEngine::Logger::GetLogger().Log(LogLevel::Warning, __VA_ARGS__)
	#define LE_ERROR(...)          ::LimeEngine::Logger::GetLogger().Log(LogLevel::Error, __VA_ARGS__)
	#define LE_CRITICAL_ERROR(...) ::LimeEngine::Logger::GetLogger().Log(LogLevel::CriticalError, __VA_ARGS__)

	#define LE_CORE(...)                ::LimeEngine::Logger::GetCoreLogger().Log(__VA_ARGS__)
	#define LE_CORE_TRACE(...)          (void)0
	#define LE_CORE_INFO(...)           ::LimeEngine::Logger::GetCoreLogger().Log(LogLevel::Info, __VA_ARGS__)
	#define LE_CORE_WARNING(...)        ::LimeEngine::Logger::GetCoreLogger().Log(LogLevel::Warning, __VA_ARGS__)
	#define LE_CORE_ERROR(...)          ::LimeEngine::Logger::GetCoreLogger().Log(LogLevel::Error, __VA_ARGS__)
	#define LE_CORE_CRITICAL_ERROR(...) ::LimeEngine::Logger::GetCoreLogger().Log(LogLevel::CriticalError, __VA_ARGS__)

#elif defined(LE_LOG_WARNINGS_AND_ERRORS)

	#define LE_LOG(...)            ::LimeEngine::Logger::GetLogger().Log(__VA_ARGS__)
	#define LE_TRACE(...)          (void)0
	#define LE_INFO(...)           (void)0
	#define LE_WARNING(...)        ::LimeEngine::Logger::GetLogger().Log(LogLevel::Warning, __VA_ARGS__)
	#define LE_ERROR(...)          ::LimeEngine::Logger::GetLogger().Log(LogLevel::Error, __VA_ARGS__)
	#define LE_CRITICAL_ERROR(...) ::LimeEngine::Logger::GetLogger().Log(LogLevel::CriticalError, __VA_ARGS__)

	#define LE_CORE(...)                ::LimeEngine::Logger::GetCoreLogger().Log(__VA_ARGS__)
	#define LE_CORE_TRACE(...)          (void)0
	#define LE_CORE_INFO(...)           (void)0
	#define LE_CORE_WARNING(...)        ::LimeEngine::Logger::GetCoreLogger().Log(LogLevel::Warning, __VA_ARGS__)
	#define LE_CORE_ERROR(...)          ::LimeEngine::Logger::GetCoreLogger().Log(LogLevel::Error, __VA_ARGS__)
	#define LE_CORE_CRITICAL_ERROR(...) ::LimeEngine::Logger::GetCoreLogger().Log(LogLevel::CriticalError, __VA_ARGS__)

#elif defined(LE_NOLOG)

	#define LE_LOG(...)            (void)0
	#define LE_TRACE(...)          (void)0
	#define LE_INFO(...)           (void)0
	#define LE_WARNING(...)        (void)0
	#define LE_ERROR(...)          (void)0
	#define LE_CRITICAL_ERROR(...) (void)0

	#define LE_CORE(...)                (void)0
	#define LE_CORE_TRACE(...)          (void)0
	#define LE_CORE_INFO(...)           (void)0
	#define LE_CORE_WARNING(...)        (void)0
	#define LE_CORE_ERROR(...)          (void)0
	#define LE_CORE_CRITICAL_ERROR(...) (void)0

#endif