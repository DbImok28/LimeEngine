#pragma once

namespace LimeEngine
{
	class Assertions
	{
	public:
#ifdef LE_ENABLE_ASSERTION
		template <typename... TArgs>
		static void Assert(bool condition, const Logger& logger, const std::format_string<TArgs...> msg, TArgs&&... args)
		{
			if (!condition)
			{
				auto formatMsg = std::format(msg, std::forward<TArgs>(args)...);
				::LimeEngine::RuntimeEditor::ShowNotification(NotificationType::Error, "Error", formatMsg, 20000);
				logger.Log(LogLevel::Error, std::format("Assertion: {0}", formatMsg));
				if (IsDebuggerPresent()) LE_DEBUGBREAK();
			}
		}
		template <typename... TArgs>
		static void CriticalAssert(bool condition, const Logger& logger, const std::format_string<TArgs...> msg, TArgs&&... args)
		{
			if (!condition)
			{
				auto formatMsg = std::format(msg, std::forward<TArgs>(args)...);
				::LimeEngine::RuntimeEditor::ShowNotification(NotificationType::Error, "Critical error", formatMsg, 30000);
				logger.Log(LogLevel::CriticalError, std::format("Critical assertion: {0}", formatMsg));
				if (IsDebuggerPresent()) LE_DEBUGBREAK();
			}
		}
		template <typename... TArgs>
		static void Warning(bool condition, const Logger& logger, const std::format_string<TArgs...> msg, TArgs&&... args)
		{
			if (!condition)
			{
				auto formatMsg = std::format(msg, std::forward<TArgs>(args)...);
				::LimeEngine::RuntimeEditor::ShowNotification(NotificationType::Warning, "Warning", formatMsg, 10000);
				logger.Log(LogLevel::Warning, std::format("Waring: {0}", formatMsg));
				if (IsDebuggerPresent()) LE_DEBUGBREAK();
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
	#define LE_CORE_WARNING(call, ...)         ::LimeEngine::Assertions::Warning(static_cast<bool>((call)), ::LimeEngine::Logger::GetCoreLogger(), __VA_ARGS__)
	#define LE_CORE_ASSERT(call, ...)          ::LimeEngine::Assertions::Assert(static_cast<bool>((call)), ::LimeEngine::Logger::GetCoreLogger(), __VA_ARGS__)
	#define LE_CORE_CRITICAL_ASSERT(call, ...) ::LimeEngine::Assertions::CriticalAssert(static_cast<bool>((call)), ::LimeEngine::Logger::GetCoreLogger(), __VA_ARGS__)

	#define LE_WARNING(call, ...)         ::LimeEngine::Assertions::Warning(static_cast<bool>((call)), ::LimeEngine::Logger::GetLogger(), __VA_ARGS__)
	#define LE_ASSERT(call, ...)          ::LimeEngine::Assertions::Assert(static_cast<bool>((call)), ::LimeEngine::Logger::GetLogger(), __VA_ARGS__)
	#define LE_CRITICAL_ASSERT(call, ...) ::LimeEngine::Assertions::CriticalAssert(static_cast<bool>((call)), ::LimeEngine::Logger::GetLogger(), __VA_ARGS__)
#else
	#define LE_CORE_WARNING(call, ...)             (void)0
	#define LE_CORE_LOG_ASSERT(call, ...)          (void)0
	#define LE_CORE_LOG_CRITICAL_ASSERT(call, ...) (void)0

	#define LE_WARNING(call, ...)             (void)0
	#define LE_LOG_ASSERT(call, ...)          (void)0
	#define LE_LOG_CRITICAL_ASSERT(call, ...) (void)0
#endif