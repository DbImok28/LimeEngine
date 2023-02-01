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
		CloseWindowEvent(int exitCode) : exitCode(exitCode) {}
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
		WindowArgs(tstring title, uint width = 1080, uint height = 720) : title(title), width(width), height(height) {}

		tstring title = "LimeEngine";
		uint width = 1080;
		uint height = 720;
	};

	class Window
	{
	public:
		static std::unique_ptr<Window> Create(const WindowArgs& args = WindowArgs());

	public:
		virtual ~Window() {}

		virtual void Init(const WindowArgs& args) = 0;
		virtual void Destroy() = 0;
		virtual void OnUpdate() = 0;
		virtual void SetTitle(const tstring& title) = 0;
		virtual uint GetWidth() const noexcept = 0;
		virtual uint GetHeight() const noexcept = 0;
		virtual void* GetHandle() const noexcept = 0;
		// TODO: Remove
		virtual InputDevice& GetInputDevice() noexcept = 0;

	public:
		MultiEventDispatcher<WindowEventType, const Event&> events;
	};
}
