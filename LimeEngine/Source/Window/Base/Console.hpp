// Copyright (C) 2022 Pavel Jakushik - All Rights Reserved
// See file LICENSE for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"

#ifdef LE_CONSOLE

	#include "Base/Color.hpp"

namespace LimeEngine
{
	class Console
	{
	public:
		inline static Console GetConsole() noexcept
		{
			return mainConsole;
		}

	private:
		static Console mainConsole;
		Console() = default;
		Console(int16 minLength, const tstring& title);

		bool Open(int16 minLength, const tstring& title) noexcept;
		bool Close() noexcept;
		void Print(tstring_view msg, PrimaryColor color = PrimaryColor::Gray) noexcept;
		void SetTitle(const tstring& title) noexcept;
		void SetMinLength(int16 minLength) const noexcept;

	private:
		bool RedirectIO() const noexcept;
		bool ReleaseIO() const noexcept;

	public:
		void* hConsole = nullptr;
	};
}

#endif