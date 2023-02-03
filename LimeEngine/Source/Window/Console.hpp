// Copyright (C) 2022 Pavel Jakushik - All Rights Reserved
// See file LICENSE for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Base/Color.hpp"

namespace LimeEngine
{
	struct ConsoleArgs
	{
		ConsoleArgs(const tstring& title = TEXT("LimeEngine output"), int16 minLength = 512) : title(title), minLength(minLength) {}
		int16 minLength;
		tstring title;
	};

	class Console
	{
#ifdef LE_CONSOLE
	private:
		static std::unique_ptr<Console> mainConsole;

	public:
		static Console& GetConsole();
#endif

	public:
		static std::unique_ptr<Console> Create(const ConsoleArgs& args);

	public:
		virtual ~Console(){};

		virtual bool Open(const ConsoleArgs& args) = 0;
		virtual bool Close() noexcept = 0;
		virtual void Print(tstring_view msg, PrimaryColor color = PrimaryColor::Gray) noexcept = 0;
		virtual void SetTitle(const tstring& title) noexcept = 0;
		virtual void SetMinLength(int16 minLength) const noexcept = 0;
	};
}
