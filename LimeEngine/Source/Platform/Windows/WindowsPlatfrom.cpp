// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#if defined(LE_BUILD_PLATFORM_WINDOWS)
	#include "Platform/Platform.hpp"

	#include "WinApi.hpp"
	#include "WindowsExceptions.hpp"
	#include "WindowsWindow.hpp"
	#include "WindowsConsole.hpp"

	#if defined(LE_ENABLE_COM)
		#include <objbase.h>
	#endif

namespace LimeEngine
{
	void Platform::Initialize()
	{
	#if defined(LE_ENABLE_COM)
		CHECK_HR(CoInitializeEx(NULL, COINIT_MULTITHREADED));
	#endif
	}

	URef<Window> Platform::MakeWindow(const WindowArgs& args)
	{
		return MakeUnique<WindowsWindow>(args);
	}

	URef<Console> Platform::MakeConsole(const ConsoleArgs& args)
	{
		return MakeUnique<WindowsConsole>(args);
	}

	bool Platform::IsDebuggerAttached() noexcept
	{
		return static_cast<bool>(IsDebuggerPresent());
	}

	FPath Platform::GetPathToExeFolder()
	{
		std::array<wchar_t, MAX_PATH> filePath = { '\0' };
		if (GetModuleFileNameW(NULL, filePath.data(), MAX_PATH) == 0)
		{
			throw HR_LAST_EXCEPTION();
		}
		return std::filesystem::path(filePath.data()).remove_filename();
	}
}

#endif
