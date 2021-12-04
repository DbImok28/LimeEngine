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
#define GFX_ERROR_INFO				dxgiErrorInfo.Set()
#define GFX_HR_EXCEPTION(hr)		GraphicsHrException(__LINE__, __FILE__, hr, dxgiErrorInfo.GetMessages())
#define GFX_ERROR_IF_MSG(call, msg)	dxgiErrorInfo.Set(); if(FAILED(hr = (call))) { auto info = dxgiErrorInfo.GetMessages(); info.push_back(msg); throw GFX_MSG_HR_EXCEPTION(hr, info);}
#define GFX_ERROR_IF(call)			dxgiErrorInfo.Set(); if(FAILED(hr = (call))) throw GFX_HR_EXCEPTION(hr)
#else
#define GFX_ERROR_INFO
#define GFX_HR_EXCEPTION(hr)		GraphicsHrException(__LINE__, __FILE__, hr)
#define GFX_ERROR_IF_MSG(call, msg)	if(FAILED(hr = (call))) throw GFX_MSG_HR_EXCEPTION(hr, msg)
#define GFX_ERROR_IF(call)			if(FAILED(hr = (call))) throw GFX_HR_EXCEPTION(hr)
#endif

#define GFX_ERROR_IF_NOINFO(call)	if(FAILED(hr = (call))) throw GraphicsHrException(__LINE__, __FILE__, hr)

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