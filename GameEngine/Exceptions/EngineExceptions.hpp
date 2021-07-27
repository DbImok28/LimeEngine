#pragma once
#include "../Window/WinApi.hpp"
#include <string>

#define HR_EXCEPTION(hr) HrException(__LINE__, __FILE__, hr)
#define HR_LAST_EXCEPTION() HrException(__LINE__, __FILE__, GetLastError())

class EngineException // : public std::exception
{
public:
	EngineException(int line, const char* file) noexcept;
	virtual const wchar_t* what() const noexcept;
	virtual const wchar_t* GetType() const noexcept;
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::wstring GetErrorLocation() const noexcept;
private:
	int line;
	std::string file;
protected:
	mutable std::wstring buffer;
};

class HrException : public EngineException
{
public:
	HrException(int line, const char* file, HRESULT hr) noexcept;
	const wchar_t* what() const noexcept override;
	const wchar_t* GetType() const noexcept override;
	HRESULT GetHr() const noexcept;
	std::wstring HrErrorString() const noexcept;
private:
	HRESULT hr;
};