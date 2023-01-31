#include "lepch.hpp"
#include "Window.hpp"
#include "CoreBase.hpp"

#if defined(LE_BUILD_PLATFORM_WINDOWS)
	#include "Window/Platform/Windows/WindowsWindow.hpp"
#endif

namespace LimeEngine
{
	std::unique_ptr<Window> Window::Create(const WindowArgs& args)
	{
#if defined(LE_BUILD_PLATFORM_WINDOWS)
		return std::make_unique<WindowsWindow>(args);
#else
		LE_CORE_ASSERT(false, "Unknown platform. Failed to create window.");
		return nullptr;
#endif
	}
}
