// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include <string>
#include <sstream>
#include "Utility/PlatformDetection.hpp"

#if defined(LE_BUILD_PLATFORM_WINDOWS)
	#include <tchar.h>

	#ifndef TEXT
		#ifdef UNICODE
			#define __TEXT(quote) L##quote
		#else
			#define __TEXT(quote) quote
		#endif
		#define TEXT(quote) __TEXT(quote)
	#endif
#else
using TCHAR = char;
using PTCHAR = char*;
	#define __TEXT(quote) quote
	#define TEXT(quote)   __TEXT(quote)
#endif

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

#if defined(LE_USE_CHARSET_UTF8)
	using Char = char8_t;
#elif defined(LE_USE_CHARSET_UTF16)
	using Char = char16_t;
#elif defined(LE_USE_CHARSET_UTF32)
	using Char = char32_t;
#else
	using Char = char8_t;
#endif

	using CString = const Char*;
	using String = std::basic_string<Char, std::char_traits<Char>, std::allocator<Char>>;
	using RefString = String&;
	using ConstString = const String&;

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
}
