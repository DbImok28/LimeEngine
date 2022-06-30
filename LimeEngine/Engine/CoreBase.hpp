#pragma once
#include <tchar.h>
#include <string>

namespace LimeEngine
{
	using tstring = std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>>;

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
}
