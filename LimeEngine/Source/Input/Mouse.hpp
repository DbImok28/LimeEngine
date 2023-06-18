#pragma once
#include "Base/Event.hpp"

namespace LimeEngine
{
	enum class MouseButton
	{
		Left,
		Right,
		Middle,
		ThumbForward,
		ThumbBack
	};

	enum class MouseEventType
	{
		LPress,
		LRelease,
		RPress,
		RRelease,
		MPress,
		MRelease,
		ThumbForwardPress,
		ThumbForwardRelease,
		ThumbBackPress,
		ThumbBackRelease,

		WheelUp,
		WheelDown,
		Move,
		RawMove,
		Enter,
		Leave,
		Invalid
	};

	class MouseEvent : public Event
	{
		EVENT_TYPE(MouseEvent);

	public:
		MouseEvent(MouseEventType mouseEventType, int x, int y) noexcept;

		MouseEventType GetMouseEventType() const noexcept;
		bool IsButtonEvent() const noexcept;
		bool IsButtonPressEvent() const noexcept;
		bool IsButtonReleaseEvent() const noexcept;
		bool IsScrollEvent() const noexcept;
		int GetMouseButton() const noexcept;

		std::pair<int, int> GetPos() const noexcept;
		int GetPosX() const noexcept;
		int GetPosY() const noexcept;

	private:
		MouseEventType mouseEventType;
		int x;
		int y;
	};

	class Mouse
	{
		friend class InputDevice;

		LE_DELETE_COPY(Mouse)

	public:
		Mouse() noexcept = default;

		void Update() noexcept;

		bool IsInWindow() const noexcept;
		bool IsLeftDown() const noexcept;
		bool IsRightDown() const noexcept;
		bool IsMiddleDown() const noexcept;
		bool IsThumbForwardDown() const noexcept;
		bool IsThumbBackDown() const noexcept;

		std::pair<int, int> GetPos() const noexcept;
		int GetPosX() const noexcept;
		int GetPosY() const noexcept;

	private:
		void OnButtonPressed(MouseButton button, int x, int y) noexcept;
		void OnButtonReleased(MouseButton button, int x, int y) noexcept;

		void OnWheelUp(int x, int y) noexcept;
		void OnWheelDown(int x, int y) noexcept;
		void OnWheelDelta(int x, int y, int delta) noexcept;

		void OnMouseMove(int x, int y) noexcept;
		void OnMouseRawMove(int x, int y) noexcept;

		void OnMouseLeave() noexcept;
		void OnMouseEnter() noexcept;

		void TrimBuffer() noexcept;

	public:
		MultiEventDispatcher<MouseEventType> events;

	private:
		std::queue<MouseEvent> buffer;
		bool leftIsDown = false;
		bool rightIsDown = false;
		bool middleIsDown = false;
		bool isInWindow = false;
		bool thumbForwardIsDown = false;
		bool thumbBackIsDown = false;
		int wheelDelta = 0;
		int x = 0;
		int y = 0;
		static constexpr size_t maxBufferSize = 16;
	};
}