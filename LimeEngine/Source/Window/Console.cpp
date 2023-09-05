// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Console.hpp"

#if defined(LE_BUILD_PLATFORM_WINDOWS)
	#include "Platform/Windows/WindowsConsole.hpp"
#endif

namespace LimeEngine
{
	std::unique_ptr<Console> Console::Create(const ConsoleArgs& args)
	{
#if defined(LE_BUILD_PLATFORM_WINDOWS)
		return std::make_unique<WindowsConsole>(args);
#else
		LE_CORE_ASSERT(false, "Unknown platform. Failed to create console.");
		return nullptr;
#endif
	}

#ifdef LE_ENABLE_CONSOLE
	std::unique_ptr<Console> Console::mainConsole = Console::Create({});

	Console& Console::GetConsole()
	{
		return *mainConsole;
	}
#endif
}
