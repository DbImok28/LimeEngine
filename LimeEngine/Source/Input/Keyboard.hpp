#pragma once

namespace LimeEngine
{
	class Keyboard
	{
		class KeyboardEvent
		{
		public:
			enum class EventType
			{
				Press,
				Release,
				Invalid
			};
			KeyboardEvent();
			KeyboardEvent(const EventType type, const unsigned char key);
			bool IsPress() const noexcept;
			bool IsRelease() const noexcept;
			bool IsValid() const noexcept;
			unsigned char GetKeyCode() const noexcept;

		private:
			EventType type;
			unsigned char key;
		};

	private:
		friend class InputDevice;

		LE_DELETE_COPY(Keyboard)

	public:
		Keyboard() = default;

		bool KeyIsPressed(const unsigned char keycode) const noexcept;

		bool KeyBufferIsEmpty() const noexcept;
		bool CharBufferIsEmpty() const noexcept;

		KeyboardEvent ReadKey() noexcept;
		char ReadChar() noexcept;

		void FlushKey() noexcept;
		void FlushChar() noexcept;
		void Flush() noexcept;

		void EnableAutoRepeatKeys() noexcept;
		void DisableAutoRepeatKeys() noexcept;
		void EnableAutoRepeatChars() noexcept;
		void DisableAutoRepeatChars() noexcept;
		bool IsKeysAutoRepeat() const noexcept;
		bool IsCharsAutoRepeat() const noexcept;

	private:
		void ClearKeyState() noexcept;

		void OnKeyPressed(const unsigned char key);
		void OnKeyReleased(const unsigned char key);
		void OnChar(const char key);

		template <typename T>
		void TrimBuffer(std::queue<T>& buffer) noexcept;

		static constexpr size_t nKeys = 256;
		static constexpr size_t maxBufferSize = 16;

		bool autoRepeatKeys = false;
		bool autoRepeatChars = true;
		std::bitset<nKeys> keyStates = false;
		std::queue<KeyboardEvent> keyBuffer;
		std::queue<char> charBuffer;
	};
}