#pragma once
#ifdef LE_ENABLE_ASSERTION
	#define LE_CORE_ASSERT(call, ...)                         \
		{                                                     \
			if (!(call))                                      \
			{                                                 \
				LE_CORE_ERROR("Assertion: {0}", __VA_ARGS__); \
				LE_DEBUGBREAK();                              \
			}                                                 \
		}
	#define LE_ASSERT(call, ...)                         \
		{                                                \
			if (!(call))                                 \
			{                                            \
				LE_ERROR("Assertion: {0}", __VA_ARGS__); \
				LE_DEBUGBREAK();                         \
			}                                            \
		}
	#define LE_CORE_CRITICAL_ASSERT(call, exception, ...)              \
		{                                                              \
			if (!(call))                                               \
			{                                                          \
				LE_CORE_CRITICAL_ERROR("Assertion: {0}", __VA_ARGS__); \
				LE_DEBUGBREAK();                                       \
			}                                                          \
		}
	#define LE_CRITICAL_ASSERT(call, exception, ...)              \
		{                                                         \
			if (!(call))                                          \
			{                                                     \
				LE_CRITICAL_ERROR("Assertion: {0}", __VA_ARGS__); \
				LE_DEBUGBREAK();                                  \
			}                                                     \
		}
#else
	#define LE_CORE_ASSERT(call, ...)
	#define LE_ASSERT(call, ...)
	#define LE_CORE_CRITICAL_ASSERT(call, exception, ...)
	#define LE_CRITICAL_ASSERT(call, exception, ...)
#endif