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

		RendererDX11(const RendererDX11&) = delete;
		RendererDX11(RendererDX11&&) noexcept = delete;
		RendererDX11& operator=(const RendererDX11&) = delete;
		RendererDX11& operator=(RendererDX11&&) noexcept = delete;

	public:
		explicit RendererDX11(Window& window);
		virtual ~RendererDX11() override = default;

	public:
		virtual void Draw(Mesh& mesh, const TempTransformMatrix& transformMatrix) override;
		void SetOutputBuffer(ID3D11Texture2D* buffer);

	private:
		void Init();
		void CreateDevice();
		void CreateDepthStencil();
		void CreateDepthStencilState();
		void CreateRasterizerState();
		void CreateSamplerState();
		void CreateViewport();

		void Render() override;
		void PreProcessing();
		void PostProcessing();

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
	};
}