// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "StringUtility.hpp"

namespace LimeEngine
{
	std::wstring StringUtility::StringToWide(const std::string& str)
	{
		return std::wstring(str.begin(), str.end());
	}

	std::string StringUtility::StringToChar8(const std::wstring& str)
	{
		return std::string(str.begin(), str.end());
	}
}