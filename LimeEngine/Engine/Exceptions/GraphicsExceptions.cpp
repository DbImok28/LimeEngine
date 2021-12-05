#include "GraphicsExceptions.hpp"

namespace LimeEngine
{
	const wchar_t* GraphicsException::GetType() const noexcept
	{
		return L"GraphicsException";
	}

	const wchar_t* GraphicsHrException::GetType() const noexcept
	{
		return L"GraphicsHrException";
	}
}