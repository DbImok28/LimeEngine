// Copyright (C) 2022 Pavel Jakushik - All Rights Reserved
// See file LICENSE for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once

#ifdef LE_BUILD_PLATFORM_WINDOWS
	#ifdef LE_BUILD_DLL
		#define LE_API __declspec(dllexport)
	#else
		#define LE_API __declspec(dllimport)
	#endif
#else
	#error Platform not supported
#endif

#define LE_CONSOLE
#define LE_LOG_FULL
#define LE_ENABLE_ASSERTION
#define LE_ENABLE_IMGUI
#define LE_ENABLE_RENDER_API_DX11

#if defined(ENABLE_RENDER_API_DX11)
	#define LE_ENABLE_COM
#endif

#include <tchar.h>
#include <string>
#include <sstream>

namespace LimeEngine
{
	using uint = unsigned int;
	using int8 = int8_t;
	using uint8 = uint8_t;
	using int16 = int16_t;
	using uint16 = uint16_t;
	using int32 = int32_t;
	using uint32 = uint32_t;
	using int64 = int64_t;
	using uint64 = uint64_t;

	using float32 = float;
	using float64 = double;
	using float96 = long double;

#define FORCEINLINE __forceinline

	// TCHAR
	using tstring = std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>>;
	using tstring_view = std::basic_string_view<TCHAR>;
	using tios = std::basic_ios<TCHAR, std::char_traits<TCHAR>>;
	using tstreambuf = std::basic_streambuf<TCHAR, std::char_traits<TCHAR>>;
	using tistream = std::basic_istream<TCHAR, std::char_traits<TCHAR>>;
	using tostream = std::basic_ostream<TCHAR, std::char_traits<TCHAR>>;
	using tiostream = std::basic_iostream<TCHAR, std::char_traits<TCHAR>>;
	using tstringbuf = std::basic_stringbuf<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>>;
	using tistringstream = std::basic_istringstream<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>>;
	using tostringstream = std::basic_ostringstream<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>>;
	using tstringstream = std::basic_stringstream<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>>;
	using tfilebuf = std::basic_filebuf<TCHAR, std::char_traits<TCHAR>>;
	using tifstream = std::basic_ifstream<TCHAR, std::char_traits<TCHAR>>;
	using tofstream = std::basic_ofstream<TCHAR, std::char_traits<TCHAR>>;
	using tfstream = std::basic_fstream<TCHAR, std::char_traits<TCHAR>>;
#ifndef TEXT
	#ifdef UNICODE
		#define __TEXT(quote) L##quote
	#else /* UNICODE */
		#define __TEXT(quote) quote
	#endif /* UNICODE */
	#define TEXT(quote) __TEXT(quote)
#endif // !TEXT
}

#include "Diagnostics/Logger.hpp"
#include "Diagnostics/RuntimeEditor.hpp"
#include "Exceptions/EngineExceptions.hpp"
#include "Base/Transform.hpp"

#ifdef LE_ENABLE_ASSERTION
	#define LE_CORE_ASSERT(call, ...)                         \
		{                                                     \
			if (!(call))                                      \
			{                                                 \
				LE_CORE_ERROR("Assertion: {0}", __VA_ARGS__); \
				__debugbreak();                               \
			}                                                 \
		}
	#define LE_ASSERT(call, ...)                         \
		{                                                \
			if (!(call))                                 \
			{                                            \
				LE_ERROR("Assertion: {0}", __VA_ARGS__); \
				__debugbreak();                          \
			}                                            \
		}
	#define LE_CORE_CRITICAL_ASSERT(call, exception, ...)              \
		{                                                              \
			if (!(call))                                               \
			{                                                          \
				LE_CORE_CRITICAL_ERROR("Assertion: {0}", __VA_ARGS__); \
				__debugbreak();                                        \
			}                                                          \
		}
	#define LE_CRITICAL_ASSERT(call, exception, ...)              \
		{                                                         \
			if (!(call))                                          \
			{                                                     \
				LE_CRITICAL_ERROR("Assertion: {0}", __VA_ARGS__); \
				__debugbreak();                                   \
			}                                                     \
		}
#else
	#define LE_CORE_ASSERT(call, ...)
	#define LE_ASSERT(call, ...)
	#define LE_CORE_CRITICAL_ASSERT(call, exception, ...)
	#define LE_CRITICAL_ASSERT(call, exception, ...)
#endif

#define LE_DELETE_COPY(ClassName)         \
	ClassName(const ClassName&) = delete; \
	ClassName& operator=(const ClassName&) = delete;

#define LE_DELETE_MOVE(ClassName)    \
	ClassName(ClassName&&) = delete; \
	ClassName& operator=(ClassName&&) = delete;

#define LE_DELETE_MOVE_COPY(ClassName) \
	LE_DELETE_COPY(ClassName)          \
	LE_DELETE_MOVE(ClassName)\
