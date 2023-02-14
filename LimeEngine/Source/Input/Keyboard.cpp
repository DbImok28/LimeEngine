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
		return keyStates[static_cast<int>(key)];
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
			char c = charBuffer.front();
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
		keyStates[static_cast<int>(key)] = true;
		keyBuffer.push(KeyboardEvent(InputActionType::Pressed, key));
		TrimBuffer(keyBuffer);
	}

	void Keyboard::OnKeyReleased(const InputKey key)
	{
		keyStates[static_cast<int>(key)] = false;
		keyBuffer.push(KeyboardEvent(InputActionType::Released, key));
		TrimBuffer(keyBuffer);
	}

	void Keyboard::OnChar(const char key)
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