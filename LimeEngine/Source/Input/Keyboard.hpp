#pragma once
#include "Base/Event.hpp"

namespace LimeEngine
{
	enum class InputActionType;
	enum class InputKey;

	class KeyboardEvent : public Event
	{
		EVENT_TYPE(KeyboardEvent);

	public:
		KeyboardEvent(const InputActionType type, const InputKey key);
		bool IsPressed() const noexcept;
		bool IsReleased() const noexcept;
		InputKey GetInputKey() const noexcept;

	private:
		InputActionType type;
		InputKey key;
	};

	class Keyboard
	{
		friend class InputDevice;

		LE_DELETE_COPY(Keyboard)

	public:
		Keyboard() = default;

		void Update() noexcept;

		bool IsKeysAutoRepeat() const noexcept;
		void EnableAutoRepeatKeys() noexcept;
		void DisableAutoRepeatKeys() noexcept;

		bool IsCharsAutoRepeat() const noexcept;
		void EnableAutoRepeatChars() noexcept;
		void DisableAutoRepeatChars() noexcept;

		bool KeyIsPressed(const InputKey key) const noexcept;

	private:
		void ClearKeyState() noexcept;

		void OnKeyPressed(const InputKey key);
		void OnKeyReleased(const InputKey key);
		void OnChar(const char key);

		template <typename T>
		void TrimBuffer(std::queue<T>& buffer) noexcept;

	public:
		MultiEventDispatcher<InputKey> keyEvents;
		EventDispatcher<char> charEvents;

	private:
		static constexpr size_t nKeys = 256;
		static constexpr size_t maxBufferSize = 16;

		bool autoRepeatKeys = false;
		bool autoRepeatChars = true;
		std::bitset<nKeys> keyStates = false;
		std::queue<KeyboardEvent> keyBuffer;
		std::queue<char> charBuffer;
	};
}