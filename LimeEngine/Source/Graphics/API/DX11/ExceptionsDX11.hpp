// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Graphics/GraphicExceptions.hpp"
#include "Platform/Windows/WindowsExceptions.hpp"

#define GFX_EXCEPTION_HR_MSG(hr, msg) LimeEngine::GraphicsHrException(__LINE__, __FILE__, hr, msg)

#ifdef LE_DEBUG

	#include "DxgiInfo.hpp"

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

	#define GFX_CHECK_INFO(call)                                                   \
		LimeEngine::dxgiErrorInfo.Set();                                           \
		(call);                                                                    \
		{                                                                          \
			auto messages = LimeEngine::dxgiErrorInfo.GetMessages();               \
			if (!messages.empty())                                                 \
			{                                                                      \
				throw LimeEngine::GraphicsException(__LINE__, __FILE__, messages); \
			}                                                                      \
		}
#else
	#define GFX_ERROR_INFO
	#define GFX_EXCEPTION_HR(hr) LimeEngine::GraphicsHrException(__LINE__, __FILE__, hr)
	#define GFX_CHECK_HR_MSG(call, msg) \
		if (HRESULT _hr = (call); FAILED(_hr)) throw GFX_EXCEPTION_HR_MSG(_hr, msg)
	#define GFX_CHECK_HR(call) \
		if (HRESULT _hr = (call); FAILED(_hr)) throw GFX_EXCEPTION_HR(_hr)
	#define GFX_CHECK_INFO(call) (call)
#endif

#define GFX_CHECK_HR_NOINFO(call) \
	if (HRESULT _hr = (call); FAILED(_hr)) throw LimeEngine::GraphicsHrException(__LINE__, __FILE__, _hr)

namespace LimeEngine
{
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
