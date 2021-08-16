#include "GraphicsExceptions.hpp"

const wchar_t* GraphicsHrException::GetType() const noexcept
{
	return L"GraphicsHrException";
}

const wchar_t* GraphicsException::GetType() const noexcept
{
	return L"GraphicsException";
}