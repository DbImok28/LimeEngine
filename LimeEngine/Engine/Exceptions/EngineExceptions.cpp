#include "EngineExceptions.hpp"
#include "../Helpers/StringHelper.hpp"
#include "../../Includes/dxerr/dxerr.h"
#include <sstream>
//#include <comdef.h>

namespace LimeEngine
{
	EngineException::EngineException(int line, const char* file) noexcept : line(line), file(file) {}

	EngineException::EngineException(int line, const char* file, std::wstring info) noexcept : line(line), file(file), info(info) {}

	EngineException::EngineException(int line, const char* file, std::vector<std::wstring> info) noexcept : line(line), file(file)
	{
		std::wostringstream oss;
		for (auto&& str : info)
			oss << str;
		this->info = oss.str();
	}

	const wchar_t* EngineException::what() const noexcept
	{
		std::wostringstream oss;
		oss << GetType() << std::endl << GetErrorLocation().c_str();
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
		oss << L"File: " << file.c_str() << std::endl << L"Line: " << line << std::endl;
		return oss.str();
	}

	std::wstring EngineException::GetErrorInfo() const noexcept
	{
		if (info.empty()) return {};
		std::wostringstream oss;
		oss << L"Info: " << info << std::endl;
		return oss.str();
	}

	EngineHrException::EngineHrException(int line, const char* file, HRESULT hr) noexcept : EngineException(line, file), hr(hr) {}

	EngineHrException::EngineHrException(int line, const char* file, HRESULT hr, std::wstring info) noexcept : EngineException(line, file, info), hr(hr) {}

	EngineHrException::EngineHrException(int line, const char* file, HRESULT hr, std::vector<std::wstring> info) noexcept : EngineException(line, file, info), hr(hr) {}

	const wchar_t* EngineHrException::what() const noexcept
	{
		std::wostringstream oss;
		oss << GetType() << std::endl << GetErrorInfo() << GetHrErrorString() << GetErrorLocation();
		buffer = oss.str();
		return buffer.c_str();
	}

	const wchar_t* EngineHrException::GetType() const noexcept
	{
		return L"EngineHrException";
	}

	HRESULT EngineHrException::GetHr() const noexcept
	{
		return hr;
	}

	std::wstring EngineHrException::GetHrErrorDescription() const noexcept
	{
		wchar_t buf[512];
#pragma warning(suppress : 6386)
		DXGetErrorDescriptionW(hr, buf, sizeof(buf));
		return buf;
	}

	std::wstring EngineHrException::GetHrErrorString() const noexcept
	{
		//_com_error errorInfo(hr);
		wchar_t* pMsg = nullptr;
		DWORD len = FormatMessageW(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr,
			hr,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			reinterpret_cast<LPWSTR>(&pMsg),
			0,
			nullptr);
		if (len == 0) return L"Unknown hr error code\n";

		std::wostringstream oss;
		oss << L"ErrorCode: " << L" - 0x" << std::hex << std::uppercase << hr << std::dec << L"(" << hr << L")" << std::endl
			<< L"Description: " << pMsg << GetHrErrorDescription() << std::endl;
		LocalFree(pMsg);
		return oss.str();
	}
}