// Copyright (C) Pavel Jakushik - All Rights Reserved
// See file LICENSE for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Input.hpp"

namespace LimeEngine
{
	InputDevice& Input::GetInputDevice() noexcept
	{
		return inputDevice;
	}

	const InputDevice& Input::GetInputDevice() const noexcept
	{
		return inputDevice;
	}

	void Input::OnKeyPressed(InputKey key) noexcept
	{
		GetInputDevice().OnKeyPressed(key);
	}

	void Input::OnKeyReleased(InputKey key) noexcept
	{
		GetInputDevice().OnKeyReleased(key);
	}

	void Input::OnKeyAxis(InputKey actionKey, float scale) noexcept
	{
		GetInputDevice().OnKeyAxis(actionKey, scale);
	}

	void Input::OnKeyAction(InputActionType type, InputKey key) noexcept
	{
		GetInputDevice().OnKeyAction(type, key);
	}

	void Input::ClearKeyState() noexcept
	{
		GetInputDevice().ClearKeyState();
	}

	void Input::OnKeyboardChar(wchar_t key) noexcept
	{
		GetInputDevice().OnKeyboardChar(key);
	}

	void Input::OnKeyboardKeyPressed(InputKey key) noexcept
	{
		GetInputDevice().OnKeyboardKeyPressed(key);
	}

	void Input::OnKeyboardKeyReleased(InputKey key) noexcept
	{
		GetInputDevice().OnKeyboardKeyReleased(key);
	}

	void Input::OnMouseKeyPressed(InputKey key, int x, int y) noexcept
	{
		GetInputDevice().OnMouseKeyPressed(key, x, y);
	}

	void Input::OnMouseKeyReleased(InputKey key, int x, int y) noexcept
	{
		GetInputDevice().OnMouseKeyReleased(key, x, y);
	}

	void Input::OnMouseWheelDelta(int x, int y, float delta) noexcept
	{
		GetInputDevice().OnMouseWheelDelta(x, y, delta);
	}

	void Input::OnMouseMove(int x, int y) noexcept
	{
		GetInputDevice().OnMouseMove(x, y);
	}

	void Input::OnMouseRawMove(int x, int y) noexcept
	{
		GetInputDevice().OnMouseRawMove(x, y);
	}

	void Input::OnMouseLeave() noexcept
	{
		GetInputDevice().OnMouseLeave();
	}

	void Input::OnMouseEnter() noexcept
	{
		GetInputDevice().OnMouseEnter();
	}
}