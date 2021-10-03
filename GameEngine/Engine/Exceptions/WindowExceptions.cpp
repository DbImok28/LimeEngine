#include "WindowExceptions.hpp"

const wchar_t* WindowException::GetType() const noexcept
{
	return L"WindowException";
}