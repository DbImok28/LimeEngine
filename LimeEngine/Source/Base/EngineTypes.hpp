// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
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
	#define __TEXT(quote) quote
	#define TEXT(quote)   __TEXT(quote)
#endif

namespace std::filesystem
{
	class path;
}

namespace LimeEngine
{
	using FPath = std::filesystem::path;

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

	template <class T>
	using Array = std::vector<T>;
	template <class T, size_t N>
	using StaticArray = std::array<T, N>;
	template <class T>
	using List = std::list<T>;

	template <typename TKey, typename TValue>
	using Map = std::map<TKey, TValue>;
	template <typename TKey, typename TValue>
	using HashMap = std::unordered_map<TKey, TValue>;

	template <typename TKey, typename TValue>
	using Set = std::set<TKey, TValue>;
	template <typename TKey, typename TValue>
	using HashSet = std::unordered_set<TKey, TValue>;

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
	using CRefString = const String&;

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

	// TODO: Add get typename function

#if !defined(__PRETTY_FUNCTION__) && !defined(__GNUC__)
	#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

	template <typename T>
	using URef = std::unique_ptr<T>;
	template <typename T>
	using SRef = std::shared_ptr<T>;
	template <typename T>
	using WRef = std::weak_ptr<T>;

	template <class T, class... Args>
	[[nodiscard]] std::enable_if_t<!std::is_array_v<T>, std::shared_ptr<T>> MakeShared(Args&&... args)
	{
		static_assert(std::is_constructible<T, Args...>::value, "The arguments provided to MakeShared do not match the constructor of the type T. " __PRETTY_FUNCTION__);
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <class T>
	[[nodiscard]] std::enable_if_t<std::is_unbounded_array_v<T>, std::shared_ptr<T>> MakeShared(const size_t count)
	{
		return std::make_shared<T>(count);
	}

	template <class T>
	[[nodiscard]] std::enable_if_t<std::is_unbounded_array_v<T>, std::shared_ptr<T>> MakeShared(const size_t count, const std::remove_extent_t<T>& val)
	{
		return std::make_shared<T>(count, val);
	}

	template <class T>
	[[nodiscard]] std::enable_if_t<std::is_bounded_array_v<T>, std::shared_ptr<T>> MakeShared()
	{
		return std::make_shared<T>();
	}

	template <class T>
	[[nodiscard]] std::enable_if_t<std::is_bounded_array_v<T>, std::shared_ptr<T>> MakeShared(const std::remove_extent_t<T>& val)
	{
		return std::make_shared<T>(val);
	}

	template <class T, class... Args, std::enable_if_t<!std::is_array_v<T>, int> = 0>
	[[nodiscard]] constexpr URef<T> MakeUnique(Args&&... args)
	{
		static_assert(std::is_constructible<T, Args...>::value, "The arguments provided to MakeUnique do not match the constructor of the type T. " __PRETTY_FUNCTION__);
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <class T, std::enable_if_t<std::is_array_v<T> && std::extent_v<T> == 0, int> = 0>
	[[nodiscard]] constexpr URef<T> MakeUnique(const size_t size)
	{
		return std::make_unique<T>(size);
	}
}
