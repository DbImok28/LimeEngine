// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once

namespace LimeEngine
{
	class Assertions
	{
		Assertions() = delete;

	public:
#ifdef LE_ENABLE_ASSERTION
		template <typename... TArgs>
		static void Assert(bool condition, const Logger* logger, std::format_string<TArgs...> msg, TArgs&&... args)
		{
			if (!condition)
			{
				auto formatMsg = std::format(msg, std::forward<TArgs>(args)...);
				::LimeEngine::RuntimeEditor::ShowNotification(NotificationType::Error, "Error", formatMsg, 20000);
				logger->Log(LogLevel::Error, "Assertion: {0}", formatMsg);
			}
		}
		template <typename... TArgs>
		static void CriticalAssert(bool condition, const Logger* logger, std::format_string<TArgs...> msg, TArgs&&... args)
		{
			if (!condition)
			{
				auto formatMsg = std::format(msg, std::forward<TArgs>(args)...);
				::LimeEngine::RuntimeEditor::ShowNotification(NotificationType::Error, "Critical error", formatMsg, 30000);
				logger->Log(LogLevel::CriticalError, "Critical assertion: {0}", formatMsg);
			}
		}
		template <typename... TArgs>
		static void Warning(bool condition, const Logger* logger, std::format_string<TArgs...> msg, TArgs&&... args)
		{
			if (!condition)
			{
				auto formatMsg = std::format(msg, std::forward<TArgs>(args)...);
				::LimeEngine::RuntimeEditor::ShowNotification(NotificationType::Warning, "Warning", formatMsg, 10000);
				logger->Log(LogLevel::Warning, "Warning: {0}", formatMsg);
			}
		}
#else
		template <typename... TArgs>
		static void Assert(bool condition, const Logger& logger, const std::format_string<TArgs...> msg, TArgs&&... args)
		{}
		template <typename... TArgs>
		static void CriticalAssert(bool condition, const Logger& logger, const std::format_string<TArgs...> msg, TArgs&&... args)
		{}
		template <typename... TArgs>
		static void Warning(bool condition, const Logger& logger, const std::format_string<TArgs...> msg, TArgs&&... args)
		{}
#endif
	};
}

#ifdef LE_ENABLE_ASSERTION

	#define LE_ASSERT_WARNING(...) LE_MACRO_OVERLOAD_ONE_OR_MANY(LE_ASSERT_WARNING, __VA_ARGS__)
	#define LE_ASSERT_WARNING_MANY(conditionExpr, ...)                                                    \
		{                                                                                                 \
			bool condition = !!(conditionExpr);                                                           \
			::LimeEngine::Assertions::Warning(condition, ::LimeEngine::Logger::GetLogger(), __VA_ARGS__); \
			if (!condition && Debugger::IsDebuggerAttached()) LE_DEBUGBREAK();                            \
		}                                                                                                 \
		LE_REQUIRE_SEMICOLON
	#define LE_ASSERT_WARNING_1(conditionExpr) LE_ASSERT_WARNING_MANY(conditionExpr, "Expression '{}' is false", #conditionExpr)

	#define LE_ASSERT(...)                     LE_MACRO_OVERLOAD_ONE_OR_MANY(LE_ASSERT, __VA_ARGS__)
	#define LE_ASSERT_MANY(conditionExpr, ...)                                                           \
		{                                                                                                \
			bool condition = !!(conditionExpr);                                                          \
			::LimeEngine::Assertions::Assert(condition, ::LimeEngine::Logger::GetLogger(), __VA_ARGS__); \
			if (!condition && Debugger::IsDebuggerAttached()) LE_DEBUGBREAK();                           \
		}                                                                                                \
		LE_REQUIRE_SEMICOLON
	#define LE_ASSERT_1(conditionExpr) LE_ASSERT_MANY(conditionExpr, "Expression '{}' is false", #conditionExpr)

	#define LE_ASSERT_CRITICAL(...)    LE_MACRO_OVERLOAD_ONE_OR_MANY(LE_ASSERT_CRITICAL, __VA_ARGS__)
	#define LE_ASSERT_CRITICAL_MANY(conditionExpr, ...)                                                          \
		{                                                                                                        \
			bool condition = !!(conditionExpr);                                                                  \
			::LimeEngine::Assertions::CriticalAssert(condition, ::LimeEngine::Logger::GetLogger(), __VA_ARGS__); \
			if (!condition && Debugger::IsDebuggerAttached()) LE_DEBUGBREAK();                                   \
		}                                                                                                        \
		LE_REQUIRE_SEMICOLON
	#define LE_ASSERT_CRITICAL_1(conditionExpr) LE_ASSERT_CRITICAL_MANY(conditionExpr, "Expression '{}' is false", #conditionExpr)

#else
	#define LE_WARNING(conditionExpr, ...)             LE_REQUIRE_SEMICOLON
	#define LE_LOG_ASSERT(conditionExpr, ...)          LE_REQUIRE_SEMICOLON
	#define LE_LOG_CRITICAL_ASSERT(conditionExpr, ...) LE_REQUIRE_SEMICOLON
#endif
