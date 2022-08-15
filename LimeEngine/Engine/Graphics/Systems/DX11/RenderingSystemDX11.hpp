// Developed by Pavel Jakushik.
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#pragma once
#include "DirectXDef.hpp"
#include "../RenderingSystem.hpp"
#include <map>
#include <string>
#include <sstream>
#include "../../../Exceptions/GraphicsExceptions.hpp"
#include "../../../Helpers/Paths.hpp"
#include "../../../Scene/CameraComponent.hpp"
#include "BindableDX11.hpp"
#include "GraphicFactoryDX11.hpp"

// TODO: Remove
#ifndef NO_IMGUI
	#ifndef IMGUI
		#define IMGUI
	#endif // !IMGUI
#endif     // !NO_IMGUI

namespace LimeEngine
{
	class RenderingSystemDX11 : public RenderingSystem
	{
		friend class BindableDX11;

	public:
		RenderingSystemDX11();
		RenderingSystemDX11(const RenderingSystemDX11&) = delete;
		RenderingSystemDX11(RenderingSystemDX11&&) noexcept = delete;
		RenderingSystemDX11& operator=(const RenderingSystemDX11&) = delete;
		RenderingSystemDX11& operator=(RenderingSystemDX11&&) noexcept = delete;
		virtual ~RenderingSystemDX11() override = default;

		virtual void SetInputCamera(CameraComponent* cameraComponent) override;
		virtual void Initialize(const Window& window) override;
		virtual void Draw(Mesh& mesh, const TempTransformMatrix& transform) override;

	private:
		void InitializeDirectX(HWND hWnd, int width, int height);
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

	public:
		CameraComponent* inputCamera = nullptr;
		// TODO: Remove
#ifdef IMGUI
	public:
		void ImGuiSetup(HWND hWnd);
		void ImGuiUpdate();
#endif // IMGUI
	};
}