// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Window/Console.hpp"

namespace LimeEngine
{
	class LE_API WindowsConsole final : public Console
	{
	public:
		WindowsConsole() = default;
		explicit WindowsConsole(const ConsoleArgs& args);
		virtual ~WindowsConsole();

		virtual bool Open(const ConsoleArgs& args) override;
		virtual bool Close() noexcept override;
		virtual void Print(tstring_view msg, PrimaryColor color = PrimaryColor::Gray) override;
		virtual void* GetHandle() const noexcept override;
		virtual void SetTitle(const tstring& title) override;
		virtual void SetMinLength(int16 minLength) const override;

	private:
		bool RedirectIO() const;
		bool ReleaseIO() const noexcept;

	private:
		void* hConsole = nullptr;
	};
}
