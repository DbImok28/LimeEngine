#include "WindowExceptions.hpp"

namespace LimeEngine
{
	const wchar_t* WindowException::GetType() const noexcept
	{
		return L"WindowException";
	}
}