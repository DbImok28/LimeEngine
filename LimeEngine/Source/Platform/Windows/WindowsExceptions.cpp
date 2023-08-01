// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "WindowsExceptions.hpp"
#include "dxerr/dxerr.h"

namespace LimeEngine
{
	EngineHrException::EngineHrException(int line, const char* file, HRESULT hr) noexcept : EngineException(line, file), hr(hr) {}

	EngineHrException::EngineHrException(int line, const char* file, HRESULT hr, const std::string& info) noexcept : EngineException(line, file, info), hr(hr) {}

	EngineHrException::EngineHrException(int line, const char* file, HRESULT hr, const std::vector<std::string>& info) noexcept : EngineException(line, file, info), hr(hr) {}

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
