// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "IBindable.hpp"
#include "Window/Window.hpp"

namespace LimeEngine
{
	enum class DisplayMode
	{
		Windowed,
		FullscreenWindowed,
		FullscreenExclusive
	};

	class RenderOutput : public IBindable
	{
	public:
		virtual ~RenderOutput() = default;
		virtual uint GetWidth() const noexcept = 0;
		virtual uint GetHeight() const noexcept = 0;

		virtual void Init() = 0;
		virtual void Present() = 0;
		virtual void Clear() = 0;
		virtual void Resize(uint width, uint height) = 0;
		virtual void OnResize(uint width, uint height) = 0;
		virtual void SetDisplayMode(DisplayMode mode) = 0;
		DisplayMode GetDisplayMode() const noexcept
		{
			return displayMode;
		}

	protected:
		DisplayMode displayMode = DisplayMode::Windowed;
	};

	class WindowRenderOutput : public RenderOutput
	{
	public:
		explicit WindowRenderOutput(Window& window, bool defaultFullscreenModeIsExclusive = false) :
			window(window), defaultFullscreenModeIsExclusive(defaultFullscreenModeIsExclusive)
		{
			window.events.Bind(WindowEventType::Resize, this, &WindowRenderOutput::OnResizeEvent);
		}
		virtual ~WindowRenderOutput()
		{
			window.events.Unbind(WindowEventType::Resize, this, &WindowRenderOutput::OnResizeEvent);
		}
		Window& GetWindow() noexcept
		{
			return window;
		}
		const Window& GetWindow() const noexcept
		{
			return window;
		}
		virtual uint GetWidth() const noexcept override
		{
			return window.GetWidth();
		}
		virtual uint GetHeight() const noexcept override
		{
			return window.GetHeight();
		}
		void SetDefaultFullscreenMode(bool isExclusive) noexcept
		{
			defaultFullscreenModeIsExclusive = isExclusive;
		}

		void OnResizeEvent(const Event& e)
		{
			auto& resizeEvent = CastEvent<ResizeWindowEvent>(e);
			OnResize(resizeEvent.width, resizeEvent.height);
		}

	protected:
		bool defaultFullscreenModeIsExclusive;
		Window& window;
	};
}
