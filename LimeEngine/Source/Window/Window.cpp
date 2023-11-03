// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Window.hpp"
#include "CoreBase.hpp"

#if defined(LE_BUILD_PLATFORM_WINDOWS)
	#include "Platform/Windows/WindowsWindow.hpp"
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

	Window::Window(std::unique_ptr<Input>&& input) noexcept : input(std::move(input)) {}

	InputDevice& Window::GetInputDevice() noexcept
	{
		return GetInput().GetInputDevice();
	}

	const InputDevice& Window::GetInputDevice() const noexcept
	{
		return GetInput().GetInputDevice();
	}

	bool Window::GetClipCursorInWindowMode() const noexcept
	{
		return clipCursorInWindowMode;
	}

	void Window::SetClipCursorInWindowMode(bool value) noexcept
	{
		clipCursorInWindowMode = value;
		UpdateCursor();
	}

	bool Window::GetClipCursorInFullScreenMode() const noexcept
	{
		return clipCursorInFullScreenMode;
	}

	void Window::SetClipCursorInFullScreenMode(bool value) noexcept
	{
		clipCursorInFullScreenMode = value;
		UpdateCursor();
	}

	Input& Window::GetInput() noexcept
	{
		return *input;
	}

	const Input& Window::GetInput() const noexcept
	{
		return *input;
	}

	bool Window::GetFullsreen() const noexcept
	{
		return fullscreen;
	}
}
