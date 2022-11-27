#pragma once
#include <string>

namespace LimeEngine
{
	class StringHelper
	{
	public:
		static std::wstring StringToWide(const std::string& str);
		static std::string StringToChar8(const std::wstring& str);
	};
}