#pragma once
#include "EngineExceptions.hpp"
#include <vector>
#include <string>
#include <sstream>

#define GFX_EXCEPTION(hr) GraphicsHrException(__LINE__, __FILE__, hr)
#define GFX_THROW_EXCEPTION_IF(hr) if(FAILED(hr)) throw GraphicsHrException(__LINE__, __FILE__, hr)

#define GFX_INFO_HR_EXCEPTION(hr, info) InfoGraphicsHrException(__LINE__, __FILE__, hr, info)
#define GFX_THROW_INFO_HR_EXCEPTION_IF(hr, info) if(FAILED(hr)) throw InfoGraphicsHrException(__LINE__, __FILE__, hr, info)

#define GFX_INFO_EXCEPTION(info) InfoGraphicsException(__LINE__, __FILE__, info)

#define GFX_ERROR_IF(hr, info) GFX_THROW_INFO_HR_EXCEPTION_IF(hr, info)

class GraphicsHrException : public HrException
{
public:
	GraphicsHrException(int line, const char* file, HRESULT hr) noexcept;
	const wchar_t* GetType() const noexcept override;
};

class InfoGraphicsHrException : public GraphicsHrException
{
public:
	InfoGraphicsHrException(int line, const char* file, HRESULT hr, std::wstring info) noexcept;
	InfoGraphicsHrException(int line, const char* file, HRESULT hr, std::vector<std::wstring> info) noexcept;
	const wchar_t* GetType() const noexcept override;
	const wchar_t* what() const noexcept override;
private:
	std::wstring info;
};

class InfoGraphicsException : public EngineException
{
public:
	InfoGraphicsException(int line, const char* file, std::wstring info) noexcept;
	InfoGraphicsException(int line, const char* file, std::vector<std::wstring> info) noexcept;
	const wchar_t* GetType() const noexcept override;
	const wchar_t* what() const noexcept override;
private:
	std::wstring info;
};