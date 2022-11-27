#include "Keyboard.hpp"

namespace LimeEngine
{
	Keyboard::KeyboardEvent::KeyboardEvent() : type(EventType::Invalid), key(-1) {}

	Keyboard::KeyboardEvent::KeyboardEvent(const EventType type, const unsigned char key) : type(type), key(key) {}

	bool Keyboard::KeyboardEvent::IsPress() const noexcept
	{
		return type == EventType::Press;
	}

	bool Keyboard::KeyboardEvent::IsRelease() const noexcept
	{
		return type == EventType::Release;
	}

	bool Keyboard::KeyboardEvent::IsValid() const noexcept
	{
		return type != EventType::Invalid;
	}

	unsigned char Keyboard::KeyboardEvent::GetKeyCode() const noexcept
	{
		return key;
	}

	bool Keyboard::KeyIsPressed(const unsigned char keycode) const noexcept
	{
		return keyStates[keycode];
	}

	bool Keyboard::KeyBufferIsEmpty() const noexcept
	{
		return keyBuffer.empty();
	}

	bool Keyboard::CharBufferIsEmpty() const noexcept
	{
		return charBuffer.empty();
	}

	Keyboard::KeyboardEvent Keyboard::ReadKey() noexcept
	{
		if (!keyBuffer.empty())
		{
			KeyboardEvent k = keyBuffer.front();
			keyBuffer.pop();
			return k;
		}
		return KeyboardEvent();
	}

	char Keyboard::ReadChar() noexcept
	{
		if (!charBuffer.empty())
		{
			char c = charBuffer.front();
			charBuffer.pop();
			return c;
		}
		return 0u;
	}

	void Keyboard::FlushKey() noexcept
	{
		keyBuffer = std::queue<Keyboard::KeyboardEvent>();
	}

	void Keyboard::FlushChar() noexcept
	{
		charBuffer = std::queue<char>();
	}

	void Keyboard::Flush() noexcept
	{
		FlushKey();
		FlushChar();
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

	void Keyboard::OnKeyPressed(const unsigned char key)
	{
		keyStates[key] = true;
		keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, key));
		TrimBuffer(keyBuffer);
	}

	void Keyboard::OnKeyReleased(const unsigned char key)
	{
		keyStates[key] = false;
		keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, key));
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