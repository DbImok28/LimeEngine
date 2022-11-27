#pragma once
#include "CoreBase.hpp"
#include "Base/Color.hpp"

namespace LimeEngine
{
	class Console
	{
	public:
		FORCEINLINE bool Open(const tstring& title) noexcept
		{
			return Open(300, title);
		}
		virtual bool Open(int16 minLength, const tstring& title) noexcept = 0;
		virtual bool Close() noexcept = 0;
		virtual void SetTitle(const tstring& title) noexcept = 0;
		virtual void Print(tstring_view msg, PrimaryColor color) noexcept = 0;
	};
}