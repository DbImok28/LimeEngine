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
#include "MeshDX11.hpp"

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
	public:
		RenderingSystemDX11();
		RenderingSystemDX11(const RenderingSystemDX11&) = delete;
		RenderingSystemDX11(RenderingSystemDX11&&) noexcept = delete;
		RenderingSystemDX11& operator=(const RenderingSystemDX11&) = delete;
		RenderingSystemDX11& operator=(RenderingSystemDX11&&) noexcept = delete;

		virtual ~RenderingSystemDX11() override = default;
		virtual void AddToRender(MeshComponent* meshComponent) override;
		virtual void RemoveFromRender(const MeshComponent* meshComponent) noexcept override;
		virtual void Render(const CameraComponent* cameraComponent) override;
		virtual void Initialize(const Window& window) override;

	private:
		void InitializeDirectX(HWND hWnd, int width, int height);
		void PreProcessing();
		void PostProcessing();

		com_ptr<IDXGISwapChain> swapchain;
		com_ptr<ID3D11RenderTargetView> renderTargetView;

		com_ptr<ID3D11DepthStencilView> depthStencilView;
		com_ptr<ID3D11Texture2D> depthStencilBuffer;
		com_ptr<ID3D11DepthStencilState> depthStencilState;

		com_ptr<ID3D11RasterizerState> rasterizerState;

		com_ptr<ID3D11SamplerState> samplerState;

	public:
		com_ptr<ID3D11Device> device;
		com_ptr<ID3D11DeviceContext> deviceContext;

	public:
		std::map<size_t, MeshDX11> renderMeshes;
		// TODO: Remove
#ifdef IMGUI
	public:
		void ImGuiSetup(HWND hWnd);
		void ImGuiUpdate();
#endif // IMGUI
	};
}