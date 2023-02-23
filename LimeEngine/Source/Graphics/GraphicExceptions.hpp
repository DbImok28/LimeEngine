#pragma once
#include "Exceptions/EngineExceptions.hpp"

#define GFX_EXCEPTION_MSG(msg) LimeEngine::GraphicsException(__LINE__, __FILE__, msg)

namespace LimeEngine
{
	class GraphicsException : public EngineException
	{
		using EngineException::EngineException;

	public:
		virtual const char* GetType() const noexcept override
		{
			return "GraphicsException";
		}
	};
}