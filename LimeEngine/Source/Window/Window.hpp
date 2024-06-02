// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Base/Event.hpp"
#include "Input/Input.hpp"

namespace LimeEngine
{
	enum class WindowEventType
	{
		Close,
		Resize,
		Focus
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
	class FocusWindowEvent : public Event
	{
		EVENT_TYPE(FocusWindowEvent);

	public:
		explicit FocusWindowEvent(bool focused) : focused(focused) {}
		bool focused;
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
		LE_DELETE_COPY(Window)

	public:
		static URef<Window> Create(const WindowArgs& args = WindowArgs());

	protected:
		Window(URef<Input>&& input) noexcept;

	public:
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;
		virtual void SetTitle(const tstring& title) = 0;
		bool GetFullsreen() const noexcept;
		virtual void SetFullsreen(bool bordered) = 0;
		virtual uint GetWidth() const noexcept = 0;
		virtual uint GetHeight() const noexcept = 0;
		virtual int GetPosX() const noexcept = 0;
		virtual int GetPosY() const noexcept = 0;
		virtual std::pair<uint, uint> GetScreenResolution() const = 0;

		virtual void* GetHandle() const noexcept = 0;
		InputDevice& GetInputDevice() noexcept;
		const InputDevice& GetInputDevice() const noexcept;

		bool GetClipCursorInWindowMode() const noexcept;
		void SetClipCursorInWindowMode(bool value) noexcept;
		bool GetClipCursorInFullScreenMode() const noexcept;
		void SetClipCursorInFullScreenMode(bool value) noexcept;
		virtual void UpdateCursor() const = 0;

		Input& GetInput() noexcept;
		const Input& GetInput() const noexcept;

	public:
		MultiEventDispatcher<WindowEventType> events;

	protected:
		bool fullscreen = false;

	private:
		URef<Input> input;
		bool clipCursorInWindowMode = false;
		bool clipCursorInFullScreenMode = true;
	};
}
