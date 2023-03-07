// Developed by Pavel Jakushik.
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#pragma once
#include "DirectXDef.hpp"
#include "Graphics/Renderer.hpp"
#include "ExceptionsDX11.hpp"
#include "Helpers/Paths.hpp"
#include "BindableDX11.hpp"
#include "GraphicFactoryDX11.hpp"

namespace LimeEngine
{
	class RendererDX11 : public Renderer
	{
		friend class BindableDX11;

		LE_DELETE_MOVE_COPY(RendererDX11)

	public:
		RendererDX11(Window& window, DisplayMode mode);
		virtual ~RendererDX11();

	public:
		virtual void Draw(Mesh& mesh, const TempTransformMatrix& transformMatrix) override;
		void SetOutputBuffer(ID3D11Texture2D* buffer);
		void Resize(uint width, uint height);
		void CreateAllBuffers();
		void DestroyAllBuffers();

	private:
		void Init(DisplayMode mode);
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

		com_ptr<ID3D11RenderTargetView> renderTargetView = nullptr;

		com_ptr<ID3D11DepthStencilView> depthStencilView = nullptr;
		com_ptr<ID3D11Texture2D> depthStencilBuffer = nullptr;
		com_ptr<ID3D11DepthStencilState> depthStencilState = nullptr;

		com_ptr<ID3D11RasterizerState> rasterizerState = nullptr;

		com_ptr<ID3D11SamplerState> samplerState = nullptr;

		com_ptr<ID3D11Device> device = nullptr;
		com_ptr<ID3D11DeviceContext> deviceContext = nullptr;
	};
}