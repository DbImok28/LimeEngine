#pragma once
#include <tchar.h>
#include <string>

namespace LimeEngine
{
	using tstring = std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>>;
}
