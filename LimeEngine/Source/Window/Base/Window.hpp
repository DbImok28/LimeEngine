// Developed by Pavel Jakushik.
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Base/Events.hpp"
#include "Input/InputDevice.hpp"

namespace LimeEngine
{
	struct WindowArgs
	{
		WindowArgs(tstring title, uint width = 1080, uint height = 720) : title(title), width(width), height(height) {}

		tstring title = "LimeEngine";
		uint width = 1080;
		uint height = 720;
	};

	class Window
	{
	public:
		virtual ~Window() {}

		virtual void Init(WindowArgs args) = 0;
		virtual void OnUpdate() = 0;
		virtual void SetTitle(const tstring& title) = 0;
		virtual uint GetWidth() const noexcept = 0;
		virtual uint GetHeight() const noexcept = 0;
		virtual void* GetHandle() const noexcept = 0;
		// TODO: Remove
		virtual InputDevice& GetInputDevice() noexcept = 0;

	public:
		EventDispatcher<int> CloseEvent;
	};
}
