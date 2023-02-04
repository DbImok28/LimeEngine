// Developed by Pavel Jakushik.
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#pragma once
#include "DirectXDef.hpp"
#include "Graphics/Renderer.hpp"
#include "Exceptions/GraphicsExceptions.hpp"
#include "Helpers/Paths.hpp"
#include "BindableDX11.hpp"
#include "GraphicFactoryDX11.hpp"

namespace LimeEngine
{
	class RendererDX11 : public Renderer
	{
		friend class BindableDX11;

	public:
		explicit RendererDX11(Window* window);
		virtual ~RendererDX11() override = default;
		RendererDX11(const RendererDX11&) = delete;
		RendererDX11(RendererDX11&&) noexcept = delete;
		RendererDX11& operator=(const RendererDX11&) = delete;
		RendererDX11& operator=(RendererDX11&&) noexcept = delete;

		void Initialize(const Window& window);
		virtual void Draw(Mesh& mesh, const TempTransformMatrix& transformMatrix) override;

	private:
		void InitializeDirectX(void* hWnd, int width, int height);
		virtual void PreProcessing() override;
		virtual void PostProcessing() override;

	public:
		virtual const GraphicFactory* GetGraphicFactory() const noexcept override;
		ID3D11Device* GetDevice() const noexcept;
		ID3D11DeviceContext* GetDeviceContext() const noexcept;

	private:
		GraphicFactoryDX11 graphicFactory;

		com_ptr<IDXGISwapChain> swapchain;
		com_ptr<ID3D11RenderTargetView> renderTargetView;

		com_ptr<ID3D11DepthStencilView> depthStencilView;
		com_ptr<ID3D11Texture2D> depthStencilBuffer;
		com_ptr<ID3D11DepthStencilState> depthStencilState;

		com_ptr<ID3D11RasterizerState> rasterizerState;

		com_ptr<ID3D11SamplerState> samplerState;

		com_ptr<ID3D11Device> device;
		com_ptr<ID3D11DeviceContext> deviceContext;

		// TODO: Remove
#ifdef IMGUI
	public:
		void ImGuiSetup(void* hWnd);
		void ImGuiUpdate();
#endif // IMGUI
	};
}