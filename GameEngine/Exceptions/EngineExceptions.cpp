#include "EngineExceptions.hpp"
#include "../Helpers/StringHelper.hpp"
#include <sstream>
//#include <comdef.h>

EngineException::EngineException(int line, const char* file) noexcept :
	line(line),
	file(file)
{}

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

std::wstring EngineException::GetErrorLocation() const noexcept
{
	std::wostringstream oss;
	oss << L"File: " << file.c_str() << std::endl
		<< L"Line: " << line << std::endl;
	return oss.str();
}

HrException::HrException(int line, const char* file, HRESULT hr) noexcept : EngineException(line, file), hr(hr) {}

const wchar_t* HrException::what() const noexcept
{
	std::wostringstream oss;
	oss << HrErrorString()
		<< GetErrorLocation();
	buffer = oss.str();
	return buffer.c_str();
}

const wchar_t* HrException::GetType() const noexcept
{
	return L"HrException";
}

HRESULT HrException::GetHr() const noexcept
{
	return hr;
}

std::wstring HrException::HrErrorString() const noexcept
{
	//_com_error errorInfo(hr);
	wchar_t* pMsg = nullptr;
	DWORD len = FormatMessageW(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPWSTR>(&pMsg), 0, nullptr);
	if (len == 0)
		return L"Unknown hr error code\n";

	std::wostringstream oss;
	oss << L"ErrorCode: " << L" - 0x" << std::hex << std::uppercase << hr << std::dec << L"(" << hr << L")" << std::endl
		<< L"Description: " << pMsg;// << std::endl;
	LocalFree(pMsg);
	return oss.str();
}