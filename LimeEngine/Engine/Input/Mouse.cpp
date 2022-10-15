#include "Mouse.hpp"
#include "Window/Windows/WinApi.hpp"

namespace LimeEngine
{
	Mouse::MouseEvent::MouseEvent() noexcept : x(0), y(0), type(MouseEvent::EventType::Invalid) {}

	Mouse::MouseEvent::MouseEvent(const EventType type, const int x, const int y) noexcept : x(x), y(y), type(type) {}

	Mouse::MouseEvent::MouseEvent(const EventType type, const std::pair<int, int>& pos) noexcept : x(pos.first), y(pos.second), type(type) {}

	bool Mouse::MouseEvent::IsValid() const noexcept
	{
		return type != MouseEvent::EventType::Invalid;
	}

	Mouse::MouseEvent::EventType Mouse::MouseEvent::GetType() const noexcept
	{
		return type;
	}

	std::pair<int, int> Mouse::MouseEvent::GetPos() const noexcept
	{
		return { x, y };
	}

	int Mouse::MouseEvent::GetPosX() const noexcept
	{
		return x;
	}

	int Mouse::MouseEvent::GetPosY() const noexcept
	{
		return y;
	}

	bool Mouse::IsInWindow() const noexcept
	{
		return isInWindow;
	}

	bool Mouse::IsLeftDown() const noexcept
	{
		return leftIsDown;
	}

	bool Mouse::IsRightDown() const noexcept
	{
		return rightIsDown;
	}

	bool Mouse::IsMiddleDown() const noexcept
	{
		return middleIsDown;
	}

	std::pair<int, int> Mouse::GetPos() const noexcept
	{
		return { x, y };
	}

	int Mouse::GetPosX() const noexcept
	{
		return x;
	}

	int Mouse::GetPosY() const noexcept
	{
		return y;
	}

	bool Mouse::EventBufferIsEmpty() const noexcept
	{
		return buffer.empty();
	}

	Mouse::MouseEvent Mouse::ReadEvent() noexcept
	{
		if (!buffer.empty())
		{
			auto e = buffer.front();
			buffer.pop();
			return e;
		}
		return MouseEvent();
	}

	void Mouse::Flush() noexcept
	{
		buffer = std::queue<Mouse::MouseEvent>();
	}

	void Mouse::OnLeftPressed(int x, int y) noexcept
	{
		leftIsDown = true;
		buffer.push(MouseEvent(MouseEvent::EventType::LPress, x, y));
		TrimBuffer();
	}

	void Mouse::OnLeftReleased(int x, int y) noexcept
	{
		leftIsDown = false;
		buffer.push(MouseEvent(MouseEvent::EventType::LRelease, x, y));
		TrimBuffer();
	}

	void Mouse::OnRightPressed(int x, int y) noexcept
	{
		rightIsDown = true;
		buffer.push(MouseEvent(MouseEvent::EventType::RPress, x, y));
		TrimBuffer();
	}

	void Mouse::OnRightReleased(int x, int y) noexcept
	{
		rightIsDown = false;
		buffer.push(MouseEvent(MouseEvent::EventType::RRelease, x, y));
		TrimBuffer();
	}

	void Mouse::OnMiddlePressed(int x, int y) noexcept
	{
		middleIsDown = true;
		buffer.push(MouseEvent(MouseEvent::EventType::MPress, x, y));
		TrimBuffer();
	}

	void Mouse::OnMiddleReleased(int x, int y) noexcept
	{
		middleIsDown = false;
		buffer.push(MouseEvent(MouseEvent::EventType::MRelease, x, y));
		TrimBuffer();
	}

	void Mouse::OnWheelUp(int x, int y) noexcept
	{
		buffer.push(MouseEvent(MouseEvent::EventType::WheelUp, x, y));
		TrimBuffer();
	}

	void Mouse::OnWheelDown(int x, int y) noexcept
	{
		buffer.push(MouseEvent(MouseEvent::EventType::WheelDown, x, y));
		TrimBuffer();
	}

	void Mouse::OnWheelDelta(int x, int y, int delta) noexcept
	{
		wheelDelta += delta;
		while (wheelDelta >= WHEEL_DELTA)
		{
			wheelDelta -= WHEEL_DELTA;
			OnWheelUp(x, y);
		}
		while (wheelDelta <= -WHEEL_DELTA)
		{
			wheelDelta += WHEEL_DELTA;
			OnWheelDown(x, y);
		}
	}

	void Mouse::OnMouseMove(int x, int y) noexcept
	{
		this->x = x;
		this->y = y;
		buffer.push(MouseEvent(MouseEvent::EventType::Move, x, y));
		TrimBuffer();
	}

	void Mouse::OnMouseRawMove(int x, int y) noexcept
	{
		buffer.push(MouseEvent(MouseEvent::EventType::RawMove, x, y));
		TrimBuffer();
	}

	void Mouse::OnMouseLeave() noexcept
	{
		isInWindow = false;
		buffer.push(MouseEvent(MouseEvent::EventType::Leave, x, y));
		TrimBuffer();
	}

	void Mouse::OnMouseEnter() noexcept
	{
		isInWindow = true;
		buffer.push(MouseEvent(MouseEvent::EventType::Enter, x, y));
		TrimBuffer();
	}

	void Mouse::TrimBuffer() noexcept
	{
		while (buffer.size() > maxBufferSize)
		{
			buffer.pop();
		}
	}
}