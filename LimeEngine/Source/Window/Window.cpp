// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Window.hpp"
#include "CoreBase.hpp"
#include "Platform/Platform.hpp"

namespace LimeEngine
{
	URef<Window> Window::Create(const WindowArgs& args)
	{
		return Platform::MakeWindow();
	}

	Window::Window(URef<Input>&& input) noexcept : input(std::move(input)) {}

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
