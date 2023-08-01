// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Graphics/RenderOutput.hpp"
#include "DirectXDef.hpp"

class RendererDX11;

namespace LimeEngine
{
	class WindowRenderOutputDX11 : public WindowRenderOutput
	{
	public:
		WindowRenderOutputDX11(RendererDX11& renderer, Window& window, bool defaultFullscreenModeIsExclusive = false);
		virtual ~WindowRenderOutputDX11();

		void Init() override;
		void Bind() override;
		void Present() override;
		void Clear() override;
		void Resize(uint width, uint height) override;
		void OnResize(uint width, uint height) override;
		void SetDisplayMode(DisplayMode newMode) override;

		void OnResizeActionEvent();

		ID3D11Texture2D* GetBackBuffer() const noexcept;

	private:
		uint refreshRate = 60;

		RendererDX11& renderer;
		com_ptr<IDXGISwapChain> swapchain = nullptr;
		com_ptr<ID3D11Texture2D> backBuffer = nullptr;
	};
}
