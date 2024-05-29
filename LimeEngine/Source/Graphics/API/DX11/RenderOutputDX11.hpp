// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Graphics/RenderOutput.hpp"
#include "RenderViewportDX11.hpp"
#include "RenderTargetDX11.hpp"

class RendererDX11;

namespace LimeEngine
{
	class WindowRenderOutputDX11 : public RenderOutput
	{
	public:
		WindowRenderOutputDX11() noexcept = default;
		WindowRenderOutputDX11(const RenderOutputArgs& args);
		virtual ~WindowRenderOutputDX11();

		virtual void Init(const RenderOutputArgs& args) override;
		virtual void Create() override;
		virtual void Destroy() override;

		virtual void Bind() override;
		virtual void Present() override;
		virtual void SetDisplayMode(DisplayMode newMode) override;
		virtual void Resize(uint width, uint height) override;

	private:
		virtual void OnWindowResize(uint width, uint height) override;
		void OnResizeActionEvent();

	public:
		virtual RenderTarget& GetRenderTarget() override;
		virtual RenderViewport& GetRenderViewport() override;
		virtual DepthStencil& GetDepthStencilBuffer() override;

	public:
		EventDispatcher<float, float> OnResize;

	private:
		uint refreshRate = 60u;
		com_ptr<IDXGISwapChain> swapchain = nullptr;
		com_ptr<ID3D11Texture2D> backBuffer = nullptr;
		WindowRenderTargetDX11 renderTarget;
		DepthStencilDX11 depthStencilBuffer;
		RenderViewportDX11 viewport;
	};
}
