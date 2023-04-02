#pragma once
#ifdef LE_ENABLE_ASSERTION
	#define LE_CORE_WARNING(call, ...)                                                                           \
		{                                                                                                        \
			if (!(call))                                                                                         \
			{                                                                                                    \
				auto msg = std::format(__VA_ARGS__);                                                             \
				::LimeEngine::RuntimeEditor::ShowNotification(NotificationType::Warning, "Warning", msg, 10000); \
				LE_CORE_LOG_WARNING(std::format("Assertion: {0}", msg));                                         \
				if (IsDebuggerPresent()) LE_DEBUGBREAK();                                                        \
			}                                                                                                    \
		}
	#define LE_CORE_ASSERT(call, ...)                                                                        \
		{                                                                                                    \
			if (!(call))                                                                                     \
			{                                                                                                \
				auto msg = std::format(__VA_ARGS__);                                                         \
				::LimeEngine::RuntimeEditor::ShowNotification(NotificationType::Error, "Error", msg, 20000); \
				LE_CORE_LOG_ERROR(std::format("Assertion: {0}", msg));                                       \
				if (IsDebuggerPresent()) LE_DEBUGBREAK();                                                    \
			}                                                                                                \
		}
	#define LE_CORE_CRITICAL_ASSERT(call, ...)                                                                        \
		{                                                                                                             \
			if (!(call))                                                                                              \
			{                                                                                                         \
				auto msg = std::format(__VA_ARGS__);                                                                  \
				::LimeEngine::RuntimeEditor::ShowNotification(NotificationType::Error, "Critical error", msg, 30000); \
				LE_CORE_LOG_CRITICAL_ERROR(std::format("Assertion: {0}", msg));                                       \
				if (IsDebuggerPresent()) LE_DEBUGBREAK();                                                             \
			}                                                                                                         \
		}

	#define LE_WARNING(call, ...)                                                                                \
		{                                                                                                        \
			if (!(call))                                                                                         \
			{                                                                                                    \
				auto msg = std::format(__VA_ARGS__);                                                             \
				::LimeEngine::RuntimeEditor::ShowNotification(NotificationType::Warning, "Warning", msg, 10000); \
				LE_CORE_LOG_WARNING(std::format("Assertion: {0}", msg));                                         \
				if (IsDebuggerPresent()) LE_DEBUGBREAK();                                                        \
			}                                                                                                    \
		}
	#define LE_ASSERT(call, ...)                                                                             \
		{                                                                                                    \
			if (!(call))                                                                                     \
			{                                                                                                \
				auto msg = std::format(__VA_ARGS__);                                                         \
				::LimeEngine::RuntimeEditor::ShowNotification(NotificationType::Error, "Error", msg, 20000); \
				LE_LOG_ERROR(std::format("Assertion: {0}", msg));                                            \
				if (IsDebuggerPresent()) LE_DEBUGBREAK();                                                    \
			}                                                                                                \
		}
	#define LE_CRITICAL_ASSERT(call, ...)                                                                             \
		{                                                                                                             \
			if (!(call))                                                                                              \
			{                                                                                                         \
				auto msg = std::format(__VA_ARGS__);                                                                  \
				::LimeEngine::RuntimeEditor::ShowNotification(NotificationType::Error, "Critical error", msg, 30000); \
				LE_LOG_CRITICAL_ERROR(std::format("Assertion: {0}", msg));                                            \
				if (IsDebuggerPresent()) LE_DEBUGBREAK();                                                             \
			}                                                                                                         \
		}
#else
	#define LE_CORE_WARNING(call, ...)             (void)0
	#define LE_CORE_LOG_ASSERT(call, ...)          (void)0
	#define LE_CORE_LOG_CRITICAL_ASSERT(call, ...) (void)0

	#define LE_WARNING(call, ...)             (void)0
	#define LE_LOG_ASSERT(call, ...)          (void)0
	#define LE_LOG_CRITICAL_ASSERT(call, ...) (void)0
#endif