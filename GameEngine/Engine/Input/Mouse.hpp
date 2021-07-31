#pragma once
#include <queue>

class Mouse
{
	friend class Window;
public:
	class MouseEvent
	{
	public:
		enum class EventType
		{
			LPress,
			LRelease,
			RPress,
			RRelease,
			MPress,
			MRelease,
			WheelUp,
			WheelDown,
			Move,
			RawMove,
			Enter,
			Leave,
			Invalid
		};
	private:
		EventType type;
		int x;
		int y;
	public:
		MouseEvent() noexcept;
		MouseEvent(const EventType type, const int x, const int y) noexcept;
		MouseEvent(const EventType type, const std::pair<int, int>& pos) noexcept;
		bool IsValid() const noexcept;
		EventType GetType() const noexcept;
		std::pair<int, int> GetPos() const noexcept;
		int GetPosX() const noexcept;
		int GetPosY() const noexcept;
	};
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;

	bool IsInWindow() const noexcept;
	bool IsLeftDown() const noexcept;
	bool IsRightDown() const noexcept;
	bool IsMiddleDown() const noexcept;

	std::pair<int, int> GetPos() const noexcept;
	int GetPosX() const noexcept;
	int GetPosY() const noexcept;

	bool EventBufferIsEmpty() const noexcept;
	MouseEvent ReadEvent() noexcept;
	void Flush() noexcept;
private:
	void OnLeftPressed(int x, int y) noexcept;
	void OnLeftReleased(int x, int y) noexcept;

	void OnRightPressed(int x, int y) noexcept;
	void OnRightReleased(int x, int y) noexcept;

	void OnMiddlePressed(int x, int y) noexcept;
	void OnMiddleReleased(int x, int y) noexcept;

	void OnWheelUp(int x, int y) noexcept;
	void OnWheelDown(int x, int y) noexcept;
	void OnWheelDelta(int x, int y, int delta) noexcept;

	void OnMouseMove(int x, int y) noexcept;
	void OnMouseRawMove(int x, int y) noexcept;

	void OnMouseLeave() noexcept;
	void OnMouseEnter() noexcept;

	void TrimBuffer() noexcept;

	std::queue<MouseEvent> buffer;
	bool leftIsDown = false;
	bool rightIsDown = false;
	bool middleIsDown = false;
	bool isInWindow = false;
	int wheelDelta = 0;
	int x = 0;
	int y = 0;
	static constexpr size_t maxBufferSize = 16;
};