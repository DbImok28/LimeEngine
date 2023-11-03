// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
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
		bool AltIsPressed() const noexcept;
		bool ShiftIsPressed() const noexcept;
		bool ControlIsPressed() const noexcept;
		bool CommondIsPressed() const noexcept;
		static bool IsAltKey(const InputKey key) noexcept;
		static bool IsShiftKey(const InputKey key) noexcept;
		static bool IsControlKey(const InputKey key) noexcept;
		static bool IsCommondKey(const InputKey key) noexcept;
		static bool IsSystemKey(const InputKey key) noexcept;

	private:
		void ClearKeyState() noexcept;

		void OnKeyPressed(const InputKey key);
		void OnKeyReleased(const InputKey key);
		void OnChar(const wchar_t key);

		template <typename T>
		static void TrimBuffer(std::queue<T>& buffer) noexcept;

	public:
		MultiEventDispatcher<InputKey> keyEvents;
		EventDispatcher<wchar_t> charEvents;

	private:
		static constexpr size_t nKeys = 256;
		static constexpr size_t maxBufferSize = 16;

		std::bitset<nKeys> keyStates = false;
		std::queue<KeyboardEvent> keyBuffer;
		std::queue<wchar_t> charBuffer;
		bool autoRepeatKeys = false;
		bool autoRepeatChars = true;
	};
}