// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once

namespace LimeEngine
{
	class StringUtility
	{
	public:
		static std::wstring Char8ToWide(const std::string& str);
		static std::string WideToChar8(const std::wstring& str);
	};
}