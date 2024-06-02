// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Console.hpp"
#include "Platform/Platform.hpp"

namespace LimeEngine
{
	URef<Console> Console::Create(const ConsoleArgs& args)
	{
		return Platform::MakeConsole(args);
	}

#ifdef LE_ENABLE_CONSOLE
	URef<Console> Console::mainConsole = Console::Create({});

	Console& Console::GetConsole()
	{
		return *mainConsole;
	}
#endif
}
