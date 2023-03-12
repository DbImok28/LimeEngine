// Developed by Pavel Jakushik.
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Base/Event.hpp"
#include "Input/InputDevice.hpp"

namespace LimeEngine
{
	enum class WindowEventType
	{
		Close,
		Resize
	};
	class CloseWindowEvent : public Event
	{
		EVENT_TYPE(CloseWindowEvent);

	public:
		explicit CloseWindowEvent(int exitCode) : exitCode(exitCode) {}
		int exitCode;
	};
	class ResizeWindowEvent : public Event
	{
		EVENT_TYPE(ResizeWindowEvent);

	public:
		ResizeWindowEvent(uint width, uint height) : width(width), height(height) {}

		uint width;
		uint height;
	};

	struct WindowArgs
	{
		WindowArgs() = default;
		explicit WindowArgs(tstring title, uint width = 1080, uint height = 720) : title(title), width(width), height(height) {}

		tstring title = "LimeEngine";
		uint width = 1080;
		uint height = 720;
	};

	class Window
	{
	public:
		static std::unique_ptr<Window> Create(const WindowArgs& args = WindowArgs());

	public:
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;
		virtual void SetTitle(const tstring& title) = 0;
		virtual void SetFullsreen(bool bordered) = 0;
		virtual uint GetWidth() const noexcept = 0;
		virtual uint GetHeight() const noexcept = 0;
		virtual int GetPosX() const noexcept = 0;
		virtual int GetPosY() const noexcept = 0;
		virtual std::pair<uint, uint> GetScreenResolution() const = 0;
		virtual void* GetHandle() const noexcept = 0;
		InputDevice& GetInputDevice() noexcept;

		// Input handlers
		void OnKeyPressed(InputKey key) noexcept;
		void OnKeyReleased(InputKey key) noexcept;
		void OnKeyAxis(InputKey actionKey, float scale) noexcept;
		void OnKeyAction(InputActionType type, InputKey key) noexcept;
		void ClearKeyState() noexcept;
		void OnKeyboardChar(wchar_t key) noexcept;
		void OnKeyboardKeyPressed(InputKey key) noexcept;
		void OnKeyboardKeyReleased(InputKey key) noexcept;
		void OnMouseKeyPressed(InputKey key, int x, int y) noexcept;
		void OnMouseKeyReleased(InputKey key, int x, int y) noexcept;
		void OnMouseWheelDelta(int x, int y, int delta) noexcept;
		void OnMouseMove(int x, int y) noexcept;
		void OnMouseRawMove(int x, int y) noexcept;
		void OnMouseLeave() noexcept;
		void OnMouseEnter() noexcept;

	public:
		MultiEventDispatcher<WindowEventType> events;

	private:
		InputDevice inputDevice;
	};
}
