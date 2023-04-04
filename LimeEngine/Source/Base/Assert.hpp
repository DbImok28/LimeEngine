#pragma once

namespace LimeEngine
{
	class Assertions
	{
		Assertions() = delete;

	public:
#ifdef LE_ENABLE_ASSERTION
		template <typename... TArgs>
		static void Assert(bool condition, const Logger& logger, std::format_string<TArgs...> msg, TArgs&&... args)
		{
			if (!condition)
			{
				auto formatMsg = std::format(msg, std::forward<TArgs>(args)...);
				::LimeEngine::RuntimeEditor::ShowNotification(NotificationType::Error, "Error", formatMsg, 20000);
				logger.Log(LogLevel::Error, "Assertion: {0}", formatMsg);
			}
		}
		template <typename... TArgs>
		static void CriticalAssert(bool condition, const Logger& logger, std::format_string<TArgs...> msg, TArgs&&... args)
		{
			if (!condition)
			{
				auto formatMsg = std::format(msg, std::forward<TArgs>(args)...);
				::LimeEngine::RuntimeEditor::ShowNotification(NotificationType::Error, "Critical error", formatMsg, 30000);
				logger.Log(LogLevel::CriticalError, "Critical assertion: {0}", formatMsg);
			}
		}
		template <typename... TArgs>
		static void Warning(bool condition, const Logger& logger, std::format_string<TArgs...> msg, TArgs&&... args)
		{
			if (!condition)
			{
				auto formatMsg = std::format(msg, std::forward<TArgs>(args)...);
				::LimeEngine::RuntimeEditor::ShowNotification(NotificationType::Warning, "Warning", formatMsg, 10000);
				logger.Log(LogLevel::Warning, "Waring: {0}", formatMsg);
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
	#define LE_CORE_WARNING(conditionExpr, ...)                                                               \
		{                                                                                                     \
			bool condition = (conditionExpr);                                                                 \
			::LimeEngine::Assertions::Warning(condition, ::LimeEngine::Logger::GetCoreLogger(), __VA_ARGS__); \
			if (!condition && Debugger::IsDebuggerAttached()) LE_DEBUGBREAK();                                \
		}
	#define LE_CORE_ASSERT(conditionExpr, ...)                                                               \
		{                                                                                                    \
			bool condition = (conditionExpr);                                                                \
			::LimeEngine::Assertions::Assert(condition, ::LimeEngine::Logger::GetCoreLogger(), __VA_ARGS__); \
			if (!condition && Debugger::IsDebuggerAttached()) LE_DEBUGBREAK();                               \
		}
	#define LE_CORE_CRITICAL_ASSERT(conditionExpr, ...)                                                              \
		{                                                                                                            \
			bool condition = (conditionExpr);                                                                        \
			::LimeEngine::Assertions::CriticalAssert(condition, ::LimeEngine::Logger::GetCoreLogger(), __VA_ARGS__); \
			if (!condition && Debugger::IsDebuggerAttached()) LE_DEBUGBREAK();                                       \
		}

	#define LE_WARNING(conditionExpr, ...)                                                                \
		{                                                                                                 \
			bool condition = (conditionExpr);                                                             \
			::LimeEngine::Assertions::Warning(condition, ::LimeEngine::Logger::GetLogger(), __VA_ARGS__); \
			if (!condition && Debugger::IsDebuggerAttached()) LE_DEBUGBREAK();                            \
		}
	#define LE_ASSERT(conditionExpr, ...)                                                                \
		{                                                                                                \
			bool condition = (conditionExpr);                                                            \
			::LimeEngine::Assertions::Assert(condition, ::LimeEngine::Logger::GetLogger(), __VA_ARGS__); \
			if (!condition && Debugger::IsDebuggerAttached()) LE_DEBUGBREAK();                           \
		}
	#define LE_CRITICAL_ASSERT(conditionExpr, ...)                                                               \
		{                                                                                                        \
			bool condition = (conditionExpr);                                                                    \
			::LimeEngine::Assertions::CriticalAssert(condition, ::LimeEngine::Logger::GetLogger(), __VA_ARGS__); \
			if (!condition && Debugger::IsDebuggerAttached()) LE_DEBUGBREAK();                                   \
		}
#else
	#define LE_CORE_WARNING(conditionExpr, ...)             (void)0
	#define LE_CORE_LOG_ASSERT(conditionExpr, ...)          (void)0
	#define LE_CORE_LOG_CRITICAL_ASSERT(conditionExpr, ...) (void)0

	#define LE_WARNING(conditionExpr, ...)             (void)0
	#define LE_LOG_ASSERT(conditionExpr, ...)          (void)0
	#define LE_LOG_CRITICAL_ASSERT(conditionExpr, ...) (void)0
#endif