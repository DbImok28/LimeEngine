// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "RenderOutput.hpp"

namespace LimeEngine
{
	RenderOutput::~RenderOutput()
	{
		if (window) window->events.Unbind(WindowEventType::Resize, this, &RenderOutput::OnResizeEvent);
	}

	void RenderOutput::SetupDisplayMode(DisplayMode mode, bool isExclusive)
	{
		SetDefaultFullscreenMode(isExclusive);
		SetDisplayMode(mode);
	}

	void RenderOutput::SetDefaultFullscreenMode(bool isExclusive) noexcept
	{
		defaultFullscreenModeIsExclusive = isExclusive;
	}

	Window* RenderOutput::GetWindow() noexcept
	{
		return window;
	}

	void RenderOutput::SetWindow(Window* newWindow)
	{
		LE_CORE_ASSERT(newWindow != nullptr, "Window cannot be a null");
		if (window) window->events.Unbind(WindowEventType::Resize, this, &RenderOutput::OnResizeEvent);
		window = newWindow;
		if (window) window->events.Bind(WindowEventType::Resize, this, &RenderOutput::OnResizeEvent);
	}

	uint RenderOutput::GetWidth() const noexcept
	{
		return window->GetWidth();
	}

	uint RenderOutput::GetHeight() const noexcept
	{
		return window->GetHeight();
	}

	DisplayMode RenderOutput::GetDisplayMode() const noexcept
	{
		return displayMode;
	}

	void RenderOutput::OnResizeEvent(const Event& e)
	{
		auto& resizeEvent = CastEvent<ResizeWindowEvent>(e);
		OnResize(resizeEvent.width, resizeEvent.height);
	}
}
