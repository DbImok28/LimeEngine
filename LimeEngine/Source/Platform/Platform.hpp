// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Window/Window.hpp"

namespace LimeEngine
{
	class Platform
	{
		LE_NON_CONSTRUCTIBLE(Platform)

	public:
		static void Initialize();
		static URef<Window> MakeWindow(const WindowArgs& args = WindowArgs());
		static URef<Console> MakeConsole(const ConsoleArgs& args);

		static bool IsDebuggerAttached() noexcept;

		static FPath GetPathToExeFolder();
	};
}
