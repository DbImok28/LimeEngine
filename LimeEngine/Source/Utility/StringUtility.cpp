// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "StringUtility.hpp"

namespace LimeEngine
{
	std::wstring StringUtility::Char8ToWide(const std::string& str)
	{
		return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>{}.from_bytes(str);
	}

	std::string StringUtility::WideToChar8(const std::wstring& str)
	{
		return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>{}.to_bytes(str);
	}
}
