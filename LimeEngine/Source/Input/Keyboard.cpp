// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Keyboard.hpp"
#include "InputDevice.hpp"

namespace LimeEngine
{
	KeyboardEvent::KeyboardEvent(const InputActionType type, const InputKey key) : type(type), key(key) {}

	bool KeyboardEvent::IsPressed() const noexcept
	{
		return type == InputActionType::Pressed;
	}

	bool KeyboardEvent::IsReleased() const noexcept
	{
		return type == InputActionType::Released;
	}

	InputKey KeyboardEvent::GetInputKey() const noexcept
	{
		return key;
	}

	bool Keyboard::KeyIsPressed(const InputKey key) const noexcept
	{
		return keyStates[static_cast<size_t>(key)];
	}

	bool Keyboard::AltIsPressed() const noexcept
	{
		return KeyIsPressed(InputKey::LeftMenu) || KeyIsPressed(InputKey::RightMenu);
	}

	bool Keyboard::ShiftIsPressed() const noexcept
	{
		return KeyIsPressed(InputKey::LeftShift) || KeyIsPressed(InputKey::RightShift);
	}

	bool Keyboard::ControlIsPressed() const noexcept
	{
		return KeyIsPressed(InputKey::LeftCtrl) || KeyIsPressed(InputKey::RightCtrl);
	}

	bool Keyboard::CommondIsPressed() const noexcept
	{
		return KeyIsPressed(InputKey::LeftWin) || KeyIsPressed(InputKey::RightWin);
	}

	bool Keyboard::IsAltKey(const InputKey key) noexcept
	{
		return key == InputKey::LeftMenu || key == InputKey::RightMenu;
	}

	bool Keyboard::IsShiftKey(const InputKey key) noexcept
	{
		return key == InputKey::LeftShift || key == InputKey::RightShift;
	}

	bool Keyboard::IsControlKey(const InputKey key) noexcept
	{
		return key == InputKey::LeftCtrl || key == InputKey::RightCtrl;
	}

	bool Keyboard::IsCommondKey(const InputKey key) noexcept
	{
		return key == InputKey::LeftWin || key == InputKey::RightWin;
	}

	bool Keyboard::IsSystemKey(const InputKey key) noexcept
	{
		return IsAltKey(key) || IsShiftKey(key) || IsControlKey(key) || IsCommondKey(key);
	}

	void Keyboard::Update() noexcept
	{
		if (!keyBuffer.empty())
		{
			const auto& e = keyBuffer.front();
			keyEvents(e.GetInputKey(), e);
			keyBuffer.pop();
		}
		if (!charBuffer.empty())
		{
			const auto c = charBuffer.front();
			charEvents(c);
			charBuffer.pop();
		}
	}

	void Keyboard::EnableAutoRepeatKeys() noexcept
	{
		autoRepeatKeys = true;
	}

	void Keyboard::DisableAutoRepeatKeys() noexcept
	{
		autoRepeatKeys = false;
	}

	void Keyboard::EnableAutoRepeatChars() noexcept
	{
		autoRepeatChars = true;
	}

	void Keyboard::DisableAutoRepeatChars() noexcept
	{
		autoRepeatChars = false;
	}

	bool Keyboard::IsKeysAutoRepeat() const noexcept
	{
		return autoRepeatKeys;
	}

	bool Keyboard::IsCharsAutoRepeat() const noexcept
	{
		return autoRepeatChars;
	}

	void Keyboard::ClearKeyState() noexcept
	{
		keyStates.reset();
	}

	void Keyboard::OnKeyPressed(const InputKey key)
	{
		keyStates[static_cast<size_t>(key)] = true;
		keyBuffer.push(KeyboardEvent(InputActionType::Pressed, key));
		TrimBuffer(keyBuffer);
	}

	void Keyboard::OnKeyReleased(const InputKey key)
	{
		keyStates[static_cast<size_t>(key)] = false;
		keyBuffer.push(KeyboardEvent(InputActionType::Released, key));
		TrimBuffer(keyBuffer);
	}

	void Keyboard::OnChar(const wchar_t key)
	{
		charBuffer.push(key);
		TrimBuffer(charBuffer);
	}

	template <typename T>
	inline void Keyboard::TrimBuffer(std::queue<T>& buffer) noexcept
	{
		while (buffer.size() > maxBufferSize)
		{
			buffer.pop();
		}
	}
}