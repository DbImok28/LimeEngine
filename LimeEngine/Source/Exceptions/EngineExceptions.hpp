#pragma once
#include "Window/Platform/Windows/WinApi.hpp"

#define MSG_EXCEPTION(msg) LimeEngine::EngineException(__LINE__, __FILE__, msg)

namespace LimeEngine
{
	class EngineException : public std::exception
	{
	public:
		EngineException(int line, const char* file) noexcept;
		EngineException(int line, const char* file, const std::string& info) noexcept;
		EngineException(int line, const char* file, const std::vector<std::string>& info) noexcept;

		virtual const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		int GetLine() const noexcept;
		const std::string& GetFile() const noexcept;
		std::string GetErrorLocation() const noexcept;
		std::string GetErrorInfo() const noexcept;

	private:
		int line;
		std::string file;
		std::string info;

	protected:
		mutable std::string buffer;
	};

#if defined(LE_BUILD_PLATFORM_WINDOWS)

	#define MSG_HR_EXCEPTION(hr, msg) LimeEngine::EngineHrException(__LINE__, __FILE__, hr, msg)
	#define HR_EXCEPTION(hr)          LimeEngine::EngineHrException(__LINE__, __FILE__, hr)
	#define HR_LAST_EXCEPTION()       LimeEngine::EngineHrException(__LINE__, __FILE__, GetLastError())

	#define CHECK_HR(call) \
		if (HRESULT _hr = (call); FAILED(_hr)) throw HR_EXCEPTION(_hr);

	#define CHECK_HR_MSG(call, msg) \
		if (HRESULT _hr = (call); FAILED(_hr)) throw HR_EXCEPTION(_hr, msg);

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

#endif
}