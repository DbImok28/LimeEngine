#pragma once
#include "EngineExceptions.hpp"

#define WND_EXCEPTION(hr)    LimeEngine::WindowException(__LINE__, __FILE__, hr)
#define WND_LAST_EXCEPTION() LimeEngine::WindowException(__LINE__, __FILE__, GetLastError())

namespace LimeEngine
{
	class WindowException : public EngineHrException
	{
		using EngineHrException::EngineHrException;

	public:
		virtual const char* GetType() const noexcept override
		{
			return "WindowException";
		}
	};
}