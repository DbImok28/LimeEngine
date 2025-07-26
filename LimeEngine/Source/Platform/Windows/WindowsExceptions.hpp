// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Exceptions/EngineExceptions.hpp"
#include "Platform/Windows/WinApi.hpp"

#define MSG_HR_EXCEPTION(hr, msg) LimeEngine::EngineHrException(__LINE__, __FILE__, hr, msg)
#define HR_EXCEPTION(hr)          LimeEngine::EngineHrException(__LINE__, __FILE__, hr)
#define HR_LAST_EXCEPTION()       LimeEngine::EngineHrException(__LINE__, __FILE__, static_cast<HRESULT>(GetLastError()))

#define CHECK_HR(call) \
	if (HRESULT _hr = (call); FAILED(_hr)) throw HR_EXCEPTION(_hr)

#define CHECK_HR_MSG(call, msg) \
	if (HRESULT _hr = (call); FAILED(_hr)) throw HR_EXCEPTION(_hr, msg)

#define CHECK_LAST_ERROR(call) \
	if (!(call)) throw HR_LAST_EXCEPTION()

#define WND_EXCEPTION(hr)    LimeEngine::WindowsWindowException(__LINE__, __FILE__, hr)
#define WND_LAST_EXCEPTION() LimeEngine::WindowsWindowException(__LINE__, __FILE__, static_cast<HRESULT>(GetLastError()))

namespace LimeEngine
{
	class EngineHrException : public EngineException
	{
	public:
		EngineHrException(int line, const char* file, HRESULT hr) noexcept;
		EngineHrException(int line, const char* file, HRESULT hr, const std::string& info) noexcept;
		EngineHrException(int line, const char* file, HRESULT hr, const std::vector<std::string>& info) noexcept;

		virtual const char* what() const noexcept override;
		virtual const char* GetType() const noexcept override;
		HRESULT GetHr() const noexcept;
		std::string GetHrErrorDescription() const noexcept;
		std::string GetHrErrorString() const noexcept;

	private:
		HRESULT hr;
	};

	class WindowsWindowException : public EngineHrException
	{
		using EngineHrException::EngineHrException;

	public:
		virtual const char* GetType() const noexcept override
		{
			return "WindowsWindowException";
		}
	};
}
