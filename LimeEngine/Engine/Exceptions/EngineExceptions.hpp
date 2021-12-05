#pragma once
#include "../Window/WinApi.hpp"
#include <string>
#include <vector>

#define MSG_EXCEPTION(msg)			LimeEngine::EngineException(__LINE__, __FILE__, msg)
#define MSG_HR_EXCEPTION(hr, msg)	LimeEngine::EngineHrException(__LINE__, __FILE__, hr, msg)
#define HR_EXCEPTION(hr)			LimeEngine::EngineHrException(__LINE__, __FILE__, hr)
#define HR_LAST_EXCEPTION()			LimeEngine::EngineHrException(__LINE__, __FILE__, GetLastError())


#define ERROR_IF(hr)				if(FAILED(hr)) throw HR_EXCEPTION(hr)
#define ERROR_IF_MSG(hr, msg)		if(FAILED(hr)) throw MSG_HR_EXCEPTION(hr, msg)

namespace LimeEngine
{
	class EngineException // : public std::exception
	{
	public:
		EngineException(int line, const char* file) noexcept;
		EngineException(int line, const char* file, std::wstring info) noexcept;
		EngineException(int line, const char* file, std::vector<std::wstring> info) noexcept;

		virtual const wchar_t* what() const noexcept;
		virtual const wchar_t* GetType() const noexcept;
		int GetLine() const noexcept;
		const std::string& GetFile() const noexcept;
		std::wstring GetErrorLocation() const noexcept;
		std::wstring GetErrorInfo() const noexcept;
	private:
		int line;
		std::string file;
		std::wstring info;
	protected:
		mutable std::wstring buffer;
	};

	class EngineHrException : public EngineException
	{
	public:
		EngineHrException(int line, const char* file, HRESULT hr) noexcept;
		EngineHrException(int line, const char* file, HRESULT hr, std::wstring info) noexcept;
		EngineHrException(int line, const char* file, HRESULT hr, std::vector<std::wstring> info) noexcept;

		const wchar_t* what() const noexcept override;
		const wchar_t* GetType() const noexcept override;
		HRESULT GetHr() const noexcept;
		std::wstring GetHrErrorDescription() const noexcept;
		std::wstring GetHrErrorString() const noexcept;
	private:
		HRESULT hr;
	};
}