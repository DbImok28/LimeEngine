// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once

namespace LimeEngine
{
	class LE_API Assertions
	{
		Assertions() = delete;

	public:
#ifdef LE_ENABLE_ASSERTION
		static void Assert(const Logger& logger, const std::string& msg)
		{
			::LimeEngine::RuntimeEditor::ShowNotification(NotificationType::Error, "Error", msg, 20000);
			logger.Log(LogLevel::Error, "Assertion: {0}", msg);
		}
		static void Warning(const Logger& logger, const std::string& msg)
		{
			::LimeEngine::RuntimeEditor::ShowNotification(NotificationType::Warning, "Warning", msg, 10000);
			logger.Log(LogLevel::Warning, "Warning: {0}", msg);
		}
		template <typename... TArgs>
		static void Assert(const Logger& logger, std::format_string<TArgs...> msg, TArgs&&... args)
		{
			auto formatMsg = std::format(msg, std::forward<TArgs>(args)...);
			Assert(logger, formatMsg);
		}
		template <typename... TArgs>
		static void Warning(const Logger& logger, std::format_string<TArgs...> msg, TArgs&&... args)
		{
			auto formatMsg = std::format(msg, std::forward<TArgs>(args)...);
			Warning(logger, formatMsg);
		}
#else
		template <typename... TArgs>
		static void Assert(bool condition, const Logger& logger, const std::format_string<TArgs...> msg, TArgs&&... args)
		{}
		template <typename... TArgs>
		static void Warning(bool condition, const Logger& logger, const std::format_string<TArgs...> msg, TArgs&&... args)
		{}
		static void Assert(bool condition, const Logger& logger, const std::string& msg) {}
		static void Warning(bool condition, const Logger& logger, const std::string& msg) {}
#endif
	};

	template <typename T>
	bool IsValid(T value);

	template <>
	bool IsValid(bool value)
	{
		return value;
	}

	template <typename T>
	bool IsValid(std::is_pointer<T> value)
	{
		return value != nullptr;
	}
}

// TODO: Rewrite
#ifdef LE_ENABLE_ASSERTION

	#define LE_WARNING(...)             LE_MACRO_OVERLOAD_ONE_OR_MANY(LE_WARNING, __VA_ARGS__)
	#define LE_WARNING_1(conditionExpr) LE_WARNING_MANY(conditionExpr, "Expression '{}' is false", #conditionExpr)
	#define LE_WARNING_MANY(conditionExpr, ...)                                                       \
		if (!(!!(conditionExpr)))                                                                     \
		{                                                                                             \
			::LimeEngine::Assertions::Warning(::LimeEngine::LoggerManager::GetLogger(), __VA_ARGS__); \
			if (Debugger::IsDebuggerAttached()) LE_DEBUGBREAK();                                      \
		}                                                                                             \
		LE_REQUIRE_SEMICOLON

	#define LE_ASSERT(...)             LE_MACRO_OVERLOAD_ONE_OR_MANY(LE_ASSERT, __VA_ARGS__)
	#define LE_ASSERT_1(conditionExpr) LE_ASSERT_MANY(conditionExpr, "Expression '{}' is false", #conditionExpr)
	#define LE_ASSERT_MANY(conditionExpr, ...)                                                       \
		if (!(!!(conditionExpr)))                                                                    \
		{                                                                                            \
			::LimeEngine::Assertions::Assert(::LimeEngine::LoggerManager::GetLogger(), __VA_ARGS__); \
			if (Debugger::IsDebuggerAttached()) LE_DEBUGBREAK();                                     \
		}                                                                                            \
		LE_REQUIRE_SEMICOLON

	#define LE_VALIDATE(...)                     LE_MACRO_OVERLOAD_ONE_OR_MANY(LE_VALIDATE, __VA_ARGS__)
	#define LE_VALIDATE_1(conditionExpr)         LE_VALIDATE_MANY(conditionExpr, "Expression '{}' is false", #conditionExpr)
	#define LE_VALIDATE_MANY(conditionExpr, ...) LE_ASSERT(IsValid(conditionExpr), __VA_ARGS__)

#else
	#define LE_WARNING(conditionExpr, ...)    LE_REQUIRE_SEMICOLON
	#define LE_LOG_ASSERT(conditionExpr, ...) LE_REQUIRE_SEMICOLON
	#define LE_VALIDATE(conditionExpr, ...)   LE_REQUIRE_SEMICOLON
#endif

#include "Base/AssertTypes.hpp"
