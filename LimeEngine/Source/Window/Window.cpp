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

	InputDevice& Window::GetInputDevice() noexcept
	{
		return inputDevice;
	}

	void Window::OnKeyPressed(InputKey key) noexcept
	{
		GetInputDevice().OnKeyPressed(key);
	}

	void Window::OnKeyReleased(InputKey key) noexcept
	{
		GetInputDevice().OnKeyReleased(key);
	}

	void Window::OnKeyAxis(InputKey actionKey, float scale) noexcept
	{
		GetInputDevice().OnKeyAxis(actionKey, scale);
	}

	void Window::OnKeyAction(InputActionType type, InputKey key) noexcept
	{
		GetInputDevice().OnKeyAction(type, key);
	}

	void Window::ClearKeyState() noexcept
	{
		GetInputDevice().ClearKeyState();
	}

	void Window::OnKeyboardChar(wchar_t key) noexcept
	{
		GetInputDevice().OnKeyboardChar(key);
	}

	void Window::OnKeyboardKeyPressed(InputKey key) noexcept
	{
		GetInputDevice().OnKeyboardKeyPressed(key);
	}

	void Window::OnKeyboardKeyReleased(InputKey key) noexcept
	{
		GetInputDevice().OnKeyboardKeyReleased(key);
	}

	void Window::OnMouseKeyPressed(InputKey key, int x, int y) noexcept
	{
		GetInputDevice().OnMouseKeyPressed(key, x, y);
	}

	void Window::OnMouseKeyReleased(InputKey key, int x, int y) noexcept
	{
		GetInputDevice().OnMouseKeyReleased(key, x, y);
	}

	void Window::OnMouseWheelDelta(int x, int y, int delta) noexcept
	{
		GetInputDevice().OnMouseWheelDelta(x, y, delta);
	}

	void Window::OnMouseMove(int x, int y) noexcept
	{
		GetInputDevice().OnMouseMove(x, y);
	}

	void Window::OnMouseRawMove(int x, int y) noexcept
	{
		GetInputDevice().OnMouseRawMove(x, y);
	}

	void Window::OnMouseLeave() noexcept
	{
		GetInputDevice().OnMouseLeave();
	}

	void Window::OnMouseEnter() noexcept
	{
		GetInputDevice().OnMouseEnter();
	}
}
