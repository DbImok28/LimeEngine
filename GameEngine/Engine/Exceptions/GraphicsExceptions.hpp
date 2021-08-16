#pragma once
#include "EngineExceptions.hpp"
#include "DxgiInfo.hpp"
#include <vector>
#include <string>
#include <sstream>

#define GFX_MSG_EXCEPTION(msg)			GraphicsException(__LINE__, __FILE__, msg)
#define GFX_MSG_HR_EXCEPTION(hr, msg)	GraphicsHrException(__LINE__, __FILE__, hr, msg)

#ifndef NDEBUG
static DxgiInfo dxgiErrorInfo;

#define GFX_HR_EXCEPTION(hr) GraphicsHrException(__LINE__, __FILE__, hr, dxgiErrorInfo.GetMessages())
#define GFX_ERROR_IF_MSG(hr, msg)	if(FAILED(hr)) { auto info = dxgiErrorInfo.GetMessages(); info.push_back(msg); throw GFX_MSG_HR_EXCEPTION(hr, info);}
#else
#define GFX_HR_EXCEPTION(hr) GraphicsHrException(__LINE__, __FILE__, hr)
#define GFX_ERROR_IF_MSG(hr, msg)	if(FAILED(hr)) throw GFX_MSG_HR_EXCEPTION(hr, msg)
#endif

#define GFX_ERROR_IF(hr)			if(FAILED(hr)) throw GFX_HR_EXCEPTION(hr)
#define GFX_ERROR_IF_NOINFO(hr)		if(FAILED(hr)) throw GraphicsHrException(__LINE__, __FILE__, hr)

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