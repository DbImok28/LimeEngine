// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "RenderOutput.hpp"

#ifdef LE_ENABLE_RENDER_API_DX11
	#include "Graphics/API/DX11/RenderOutputDX11.hpp"
#endif

namespace LimeEngine
{
	URef<RenderOutput> RenderOutput::CreateWindowRenderOutput(const RenderOutputArgs& args)
	{
		switch (RenderAPI::DefaultRenderAPI)
		{
			case RenderAPIType::None: break;
#if defined(LE_ENABLE_RENDER_API_DX11)
			case RenderAPIType::DirectX11: return MakeUnique<WindowRenderOutputDX11>(args);
#endif
			default: break;
		}
		LE_ASSERT(false, "Unknown render API. Failed to create WindowRenderOutput");
		return nullptr;
	}

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
		LE_ASSERT(newWindow != nullptr, "Window cannot be a null");
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
		LE_CORE_LOG_TRACE("Resize WindowRenderOutput (width: {}, height: {})", resizeEvent.width, resizeEvent.height);
		OnWindowResize(resizeEvent.width, resizeEvent.height);
	}
}
