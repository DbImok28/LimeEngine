#pragma once
#include "../Window/WinApi.hpp"
#include <string>
#include <vector>

#define HR_EXCEPTION(hr) EngineHrException(__LINE__, __FILE__, hr)
#define HR_LAST_EXCEPTION() EngineHrException(__LINE__, __FILE__, GetLastError())

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
	std::wstring HrErrorString() const noexcept;
private:
	HRESULT hr;
};