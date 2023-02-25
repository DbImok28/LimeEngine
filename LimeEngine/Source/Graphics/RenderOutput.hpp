// Developed by Pavel Jakushik.
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#pragma once
#include "IBindable.hpp"
#include "Window/Window.hpp"

namespace LimeEngine
{
	class RenderOutput : public IBindable
	{
	public:
		virtual ~RenderOutput() = default;
		virtual uint GetWidth() const noexcept = 0;
		virtual uint GetHeight() const noexcept = 0;

		virtual void Init() = 0;
		virtual void Present() = 0;
		virtual void Resize(uint width, uint height) = 0;
	};

	class WindowRenderOutput : public RenderOutput
	{
	public:
		WindowRenderOutput(Window& window) : window(window)
		{
			window.events.Bind(WindowEventType::Resize, this, &WindowRenderOutput::OnResize);
		}
		virtual ~WindowRenderOutput()
		{
			window.events.Unbind(WindowEventType::Resize, this, &WindowRenderOutput::OnResize);
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

		void OnResize(const Event& e)
		{
			auto& resizeEvent = CastEvent<ResizeWindowEvent>(e);
			Resize(resizeEvent.width, resizeEvent.height);
		}

	protected:
		Window& window;
	};
}
