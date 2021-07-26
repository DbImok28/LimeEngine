#include "EngineExceptions.hpp"
#include "../Helpers/StringHelper.hpp"
#include <cassert>
#include <sstream>

EngineException::EngineException(int line, const char* file) noexcept :
	line(line),
	file(file)
{}

/*const char* EngineException::what() const noexcept
{
	//assert("Use Info() instead of what()!" && 0);
	Info();
	return StringHelper::StringToChar8(buffer).c_str();
}*/

const wchar_t* EngineException::what() const noexcept
{
	std::wostringstream oss;
	oss << GetType() << std::endl
		<< GetErrorLocation().c_str();
	buffer = oss.str();
	return buffer.c_str();
}

const wchar_t* EngineException::GetType() const noexcept
{
	return L"EngineException";
}

int EngineException::GetLine() const noexcept
{
	return line;
}

const std::string& EngineException::GetFile() const noexcept
{
	return file;
}

std::string EngineException::GetErrorLocation() const noexcept
{
	std::ostringstream oss;
	oss << "File: " << file << std::endl
		<< "Line: " << line;
	return oss.str();
}