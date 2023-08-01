// Copyright (C) Pavel Jakushik - All Rights Reserved
// See file LICENSE for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "InputDevice.hpp"

namespace LimeEngine
{
	class Input
	{
	public:
		virtual ~Input() = default;

		InputDevice& GetInputDevice() noexcept;
		const InputDevice& GetInputDevice() const noexcept;

	protected:
		void OnKeyPressed(InputKey key) noexcept;
		void OnKeyReleased(InputKey key) noexcept;
		void OnKeyAxis(InputKey actionKey, float scale) noexcept;
		void OnKeyAction(InputActionType type, InputKey key) noexcept;
		void ClearKeyState() noexcept;
		void OnKeyboardChar(wchar_t key) noexcept;
		void OnKeyboardKeyPressed(InputKey key) noexcept;
		void OnKeyboardKeyReleased(InputKey key) noexcept;

		void OnMouseKeyPressed(InputKey key, int x, int y) noexcept;
		void OnMouseKeyReleased(InputKey key, int x, int y) noexcept;
		void OnMouseWheelDelta(int x, int y, float delta) noexcept;
		void OnMouseMove(int x, int y) noexcept;
		void OnMouseRawMove(int x, int y) noexcept;
		void OnMouseLeave() noexcept;
		void OnMouseEnter() noexcept;

	private:
		InputDevice inputDevice;
	};
}
