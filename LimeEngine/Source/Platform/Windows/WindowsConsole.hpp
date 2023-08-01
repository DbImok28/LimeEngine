// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Window/Console.hpp"

namespace LimeEngine
{
	class WindowsConsole final : public Console
	{
	public:
		WindowsConsole() = default;
		explicit WindowsConsole(const ConsoleArgs& args);
		virtual ~WindowsConsole();

		bool Open(const ConsoleArgs& args) override;
		bool Close() noexcept override;
		void Print(tstring_view msg, PrimaryColor color = PrimaryColor::Gray) noexcept override;
		void SetTitle(const tstring& title) noexcept override;
		void SetMinLength(int16 minLength) const noexcept override;

	private:
		bool RedirectIO() const noexcept;
		bool ReleaseIO() const noexcept;

	private:
		void* hConsole = nullptr;
	};
}
