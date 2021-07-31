#include "StringHelper.hpp"

std::wstring StringHelper::StringToWide(const std::string& str)
{
	return std::wstring(str.begin(), str.end());
}

std::string StringHelper::StringToChar8(const std::wstring& str)
{
	return std::string(str.begin(), str.end());
}