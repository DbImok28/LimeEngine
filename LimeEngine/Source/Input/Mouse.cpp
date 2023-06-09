#include "lepch.hpp"
#include "Mouse.hpp"

namespace LimeEngine
{
	MouseEvent::MouseEvent(MouseEventType mouseEventType, int x, int y) noexcept : mouseEventType(mouseEventType), x(x), y(y) {}

	MouseEventType MouseEvent::GetMouseEventType() const noexcept
	{
		return mouseEventType;
	}

	bool MouseEvent::IsButtonEvent() const noexcept
	{
		return IsButtonPressEvent() || IsButtonReleaseEvent();
	}

	bool MouseEvent::IsButtonPressEvent() const noexcept
	{
		return mouseEventType == MouseEventType::LPress || mouseEventType == MouseEventType::RPress || mouseEventType == MouseEventType::MPress;
	}

	bool MouseEvent::IsButtonReleaseEvent() const noexcept
	{
		return mouseEventType == MouseEventType::LRelease || mouseEventType == MouseEventType::RRelease || mouseEventType == MouseEventType::MRelease;
	}

	bool MouseEvent::IsScrollEvent() const noexcept
	{
		return mouseEventType == MouseEventType::WheelUp || mouseEventType == MouseEventType::WheelDown;
	}

	int MouseEvent::GetMouseButton() const noexcept
	{
		switch (mouseEventType)
		{
			case LimeEngine::MouseEventType::LPress:
			case LimeEngine::MouseEventType::LRelease: return 0;
			case LimeEngine::MouseEventType::RPress:
			case LimeEngine::MouseEventType::RRelease: return 1;
			case LimeEngine::MouseEventType::MPress:
			case LimeEngine::MouseEventType::MRelease: return 2;
			default: return -1;
		}
	}

	std::pair<int, int> MouseEvent::GetPos() const noexcept
	{
		return { x, y };
	}

	int MouseEvent::GetPosX() const noexcept
	{
		return x;
	}

	int MouseEvent::GetPosY() const noexcept
	{
		return y;
	}

	void Mouse::Update() noexcept
	{
		while (!buffer.empty())
		{
			const auto& e = buffer.front();
			events(e.GetMouseEventType(), e);
			buffer.pop();
		}
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

	void Mouse::OnButtonPressed(MouseButton button, int x, int y) noexcept
	{
		switch (button)
		{
			case LimeEngine::MouseButton::Left:
				buffer.emplace(MouseEventType::LPress, x, y);
				leftIsDown = true;
				break;
			case LimeEngine::MouseButton::Right:
				buffer.emplace(MouseEventType::RPress, x, y);
				rightIsDown = true;
				break;
			case LimeEngine::MouseButton::Middle:
				buffer.emplace(MouseEventType::MPress, x, y);
				middleIsDown = true;
				break;
			default: break;
		}
		TrimBuffer();
	}

	void Mouse::OnButtonReleased(MouseButton button, int x, int y) noexcept
	{
		switch (button)
		{
			case LimeEngine::MouseButton::Left:
				buffer.emplace(MouseEventType::LRelease, x, y);
				leftIsDown = false;
				break;
			case LimeEngine::MouseButton::Right:
				buffer.emplace(MouseEventType::RRelease, x, y);
				rightIsDown = false;
				break;
			case LimeEngine::MouseButton::Middle:
				buffer.emplace(MouseEventType::MRelease, x, y);
				middleIsDown = false;
				break;
			default: break;
		}
		TrimBuffer();
	}

	void Mouse::OnWheelUp(int x, int y) noexcept
	{
		buffer.emplace(MouseEventType::WheelUp, x, y);
		TrimBuffer();
	}

	void Mouse::OnWheelDown(int x, int y) noexcept
	{
		buffer.emplace(MouseEventType::WheelDown, x, y);
		TrimBuffer();
	}

	void Mouse::OnWheelDelta(int x, int y, int delta) noexcept
	{
		wheelDelta += delta;
		while (wheelDelta > 1)
		{
			wheelDelta -= 1;
			OnWheelUp(x, y);
		}
		while (wheelDelta < 1)
		{
			wheelDelta += 1;
			OnWheelDown(x, y);
		}
	}

	void Mouse::OnMouseMove(int x, int y) noexcept
	{
		this->x = x;
		this->y = y;
		buffer.push(MouseEvent(MouseEventType::Move, x, y));
		TrimBuffer();
	}

	void Mouse::OnMouseRawMove(int x, int y) noexcept
	{
		buffer.push(MouseEvent(MouseEventType::RawMove, x, y));
		TrimBuffer();
	}

	void Mouse::OnMouseLeave() noexcept
	{
		isInWindow = false;
		buffer.push(MouseEvent(MouseEventType::Leave, x, y));
		TrimBuffer();
	}

	void Mouse::OnMouseEnter() noexcept
	{
		isInWindow = true;
		buffer.push(MouseEvent(MouseEventType::Enter, x, y));
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