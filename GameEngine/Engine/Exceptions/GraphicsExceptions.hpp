#pragma once
#include "EngineExceptions.hpp"
#include <vector>
#include <string>
#include <sstream>

#define GFX_EXCEPTION(hr) GraphicsHrException(__LINE__, __FILE__, hr)
#define GFX_THROW_EXCEPTION_IF(hr) if(FAILED(hr)) throw GraphicsHrException(__LINE__, __FILE__, hr)

#define GFX_INFO_HR_EXCEPTION(hr, info) GraphicsHrException(__LINE__, __FILE__, hr, info)
#define GFX_THROW_INFO_HR_EXCEPTION_IF(hr, info) if(FAILED(hr)) throw GraphicsHrException(__LINE__, __FILE__, hr, info)

#define GFX_INFO_EXCEPTION(info) GraphicsException(__LINE__, __FILE__, info)

#define GFX_ERROR_IF(hr, info) GFX_THROW_INFO_HR_EXCEPTION_IF(hr, info)

class GraphicsException : public EngineException
{
	using EngineException::EngineException;
public:
	const wchar_t* GetType() const noexcept override;
};

class GraphicsHrException : public EngineHrException
{
	using EngineHrException::EngineHrException;
public:
	const wchar_t* GetType() const noexcept override;
};