// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Graphics/RenderOutput.hpp"
#include "DirectXDef.hpp"

class RendererDX11;

namespace LimeEngine
{
	class WindowRenderOutputDX11 : public RenderOutput
	{
	public:
		WindowRenderOutputDX11() noexcept = default;
		virtual ~WindowRenderOutputDX11();

		virtual void Init(const RenderOutputArgs& args) override;
		virtual void Create() override;
		virtual void Destroy() override;

		virtual void Bind() override;
		virtual void Present() override;
		virtual void Resize(uint width, uint height) override;
		virtual void SetDisplayMode(DisplayMode newMode) override;

	private:
		virtual void OnResize(uint width, uint height) override;
		void OnResizeActionEvent();

	public:
		ID3D11Texture2D* GetBackBuffer() const noexcept;

	private:
		uint refreshRate = 60u;
		com_ptr<IDXGISwapChain> swapchain = nullptr;
		com_ptr<ID3D11Texture2D> backBuffer = nullptr;
	};
}
