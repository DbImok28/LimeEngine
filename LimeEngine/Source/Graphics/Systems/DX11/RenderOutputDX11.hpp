// Developed by Pavel Jakushik.
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Graphics/RenderOutput.hpp"
#include "DirectXDef.hpp"

class RendererDX11;

namespace LimeEngine
{
	class WindowRenderOutputDX11 : public WindowRenderOutput
	{
	public:
		WindowRenderOutputDX11(RendererDX11& renderer, Window& window);
		virtual ~WindowRenderOutputDX11() {}

		void Init() override;
		void Bind() override;
		void Present() override;

		ID3D11Texture2D* GetBackBuffer() const noexcept;

	private:
		RendererDX11& renderer;
		com_ptr<IDXGISwapChain> swapchain;
		com_ptr<ID3D11Texture2D> backBuffer;
		bool binded = false;
	};
}
