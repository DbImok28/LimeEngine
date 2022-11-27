#pragma once
#include "EngineExceptions.hpp"
#include "DxgiInfo.hpp"
#include <vector>
#include <string>
#include <sstream>

#define GFX_EXCEPTION_MSG(msg)        LimeEngine::GraphicsException(__LINE__, __FILE__, msg)
#define GFX_EXCEPTION_HR_MSG(hr, msg) LimeEngine::GraphicsHrException(__LINE__, __FILE__, hr, msg)

#ifndef NDEBUG
namespace LimeEngine
{
	static DxgiInfo dxgiErrorInfo;
}
	#define GFX_ERROR_INFO       LimeEngine::dxgiErrorInfo.Set()
	#define GFX_EXCEPTION_HR(hr) LimeEngine::GraphicsHrException(__LINE__, __FILE__, hr, LimeEngine::dxgiErrorInfo.GetMessages())
	#define GFX_CHECK_HR_MSG(call, msg)                          \
		LimeEngine::dxgiErrorInfo.Set();                         \
		if (HRESULT _hr = (call); FAILED(_hr))                   \
		{                                                        \
			auto info = LimeEngine::dxgiErrorInfo.GetMessages(); \
			info.push_back(msg);                                 \
			throw GFX_EXCEPTION_HR_MSG(_hr, info);               \
		}
	#define GFX_CHECK_HR(call)           \
		LimeEngine::dxgiErrorInfo.Set(); \
		if (HRESULT _hr = (call); FAILED(_hr)) throw GFX_EXCEPTION_HR(_hr)
#else
	#define GFX_ERROR_INFO
	#define GFX_EXCEPTION_HR(hr) LimeEngine::GraphicsHrException(__LINE__, __FILE__, hr)
	#define GFX_CHECK_HR_MSG(call, msg) \
		if (HRESULT _hr = (call); FAILED(_hr)) throw GFX_EXCEPTION_HR_MSG(_hr, msg)
	#define GFX_CHECK_HR(call) \
		if (HRESULT _hr = (call); FAILED(_hr)) throw GFX_HR_EXCEPTION(_hr)
#endif

#define GFX_ERROR_IF_NOINFO(call) \
	if (FAILED(hr = (call))) throw LimeEngine::GraphicsHrException(__LINE__, __FILE__, hr)

namespace LimeEngine
{
	class GraphicsException : public EngineException
	{
		using EngineException::EngineException;

	public:
		virtual const char* GetType() const noexcept override
		{
			return "GraphicsHrException";
		}
	};

	class GraphicsHrException : public EngineHrException
	{
		using EngineHrException::EngineHrException;

	public:
		virtual const char* GetType() const noexcept override
		{
			return "GraphicsHrException";
		}
	};
}