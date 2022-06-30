#include "EngineExceptions.hpp"
#include "../Helpers/StringHelper.hpp"
#include "../../Includes/dxerr/dxerr.h"
#include <sstream>
//#include <comdef.h>

namespace LimeEngine
{
	EngineException::EngineException(int line, const char* file) noexcept : line(line), file(file) {}

	EngineException::EngineException(int line, const char* file, std::string info) noexcept : line(line), file(file), info(info) {}

	EngineException::EngineException(int line, const char* file, std::vector<std::string> info) noexcept : line(line), file(file)
	{
		std::ostringstream oss;
		for (auto&& str : info)
			oss << str;
		this->info = oss.str();
	}

	const char* EngineException::what() const noexcept
	{
		std::ostringstream oss;
		oss << GetType() << std::endl << GetErrorLocation().c_str();
		buffer = oss.str();
		return buffer.c_str();
	}

	const char* EngineException::GetType() const noexcept
	{
		return "EngineException";
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
		oss << "File: " << file.c_str() << std::endl << "Line: " << line << std::endl;
		return oss.str();
	}

	std::string EngineException::GetErrorInfo() const noexcept
	{
		if (info.empty()) return {};
		std::ostringstream oss;
		oss << "Info: " << info << std::endl;
		return oss.str();
	}

	EngineHrException::EngineHrException(int line, const char* file, HRESULT hr) noexcept : EngineException(line, file), hr(hr) {}

	EngineHrException::EngineHrException(int line, const char* file, HRESULT hr, std::string info) noexcept : EngineException(line, file, info), hr(hr) {}

	EngineHrException::EngineHrException(int line, const char* file, HRESULT hr, std::vector<std::string> info) noexcept : EngineException(line, file, info), hr(hr) {}

	const char* EngineHrException::what() const noexcept
	{
		std::ostringstream oss;
		oss << GetType() << std::endl << GetErrorInfo() << GetHrErrorString() << GetErrorLocation();
		buffer = oss.str();
		return buffer.c_str();
	}

	const char* EngineHrException::GetType() const noexcept
	{
		return "EngineHrException";
	}

	HRESULT EngineHrException::GetHr() const noexcept
	{
		return hr;
	}

	std::string EngineHrException::GetHrErrorDescription() const noexcept
	{
		char buf[512];
#pragma warning(suppress : 6386)
		DXGetErrorDescriptionA(hr, buf, sizeof(buf));
		return buf;
	}

	std::string EngineHrException::GetHrErrorString() const noexcept
	{
		//_com_error errorInfo(hr);
		char* pMsg = nullptr;
		DWORD len = FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr,
			hr,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			reinterpret_cast<LPSTR>(&pMsg),
			0,
			nullptr);
		if (len == 0) return "Unknown hr error code\n";

		std::ostringstream oss;
		oss << "ErrorCode: "
			<< " - 0x" << std::hex << std::uppercase << hr << std::dec << "(" << hr << ")" << std::endl
			<< "Description: " << pMsg << GetHrErrorDescription() << std::endl;
		LocalFree(pMsg);
		return oss.str();
	}
}