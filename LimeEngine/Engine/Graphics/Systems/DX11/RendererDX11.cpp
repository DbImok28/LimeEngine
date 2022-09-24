#include "RendererDX11.hpp"
#include "GraphicAdapter.hpp"
#include "../../../Scene/MeshComponent.hpp"
#include "../../Base/Mesh.hpp"

#ifdef IMGUI
	#include "ImGui/imgui.h"
	#include "ImGui/imgui_impl_win32.h"
	#include "ImGui/imgui_impl_dx11.h"
#endif // IMGUI

namespace LimeEngine
{
	RendererDX11::RendererDX11(Window* window) : Renderer(window), graphicFactory(*this)
	{
		Initialize(*window);
	}

	void RendererDX11::Initialize(const Window& window)
	{
		InitializeDirectX(window.GetHWnd(), window.width, window.height);
#ifdef IMGUI
		ImGuiSetup(window.GetHWnd());
#endif // IMGUI
	}

	void RendererDX11::Draw(Mesh& mesh, const TempTransformMatrix& transformMatrix)
	{
		if (!(inputCamera && mesh.GetMaterial())) return;
		mesh.BindRenderData(mesh.GetMaterial(), inputCamera, transformMatrix);
		deviceContext->DrawIndexed(mesh.IndicesCount(), 0, 0);
	}

	const GraphicFactory* RendererDX11::GetGraphicFactory() const noexcept
	{
		return &graphicFactory;
	}

	ID3D11Device* RendererDX11::GetDevice() const noexcept
	{
		return device.Get();
	}

	ID3D11DeviceContext* RendererDX11::GetDeviceContext() const noexcept
	{
		return deviceContext.Get();
	}

	void RendererDX11::InitializeDirectX(HWND hWnd, int width, int height)
	{
		/*
		1  Input Assembler		(IA) Stage
		2  Vertex Shader		(VS) Stage
		3  Hull Shader			(HS) Stage
		4  Tessellator Shader	(TS) Stage
		5  Domain Shader		(DS) Stage
		6  Geometry Shader		(GS) Stage
		7  Stream Output		(SO) Stage
		8  Rasterizer			(RS) Stage
		9  Pixel Shader			(PS) Stage
		10 Output Merger		(OM) Stage
		*/
		std::vector<GraphicAdapter> adapters = GraphicAdapter::GetGraphicAdapters();
		if (adapters.size() < 1) throw GFX_EXCEPTION_MSG("No found DXGI Adapters.");

		DXGI_SWAP_CHAIN_DESC scd = { 0 };

		scd.BufferDesc.Width = width;
		scd.BufferDesc.Height = height;
		scd.BufferDesc.RefreshRate.Numerator = 60;
		scd.BufferDesc.RefreshRate.Denominator = 1;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		scd.SampleDesc.Count = 1;
		scd.SampleDesc.Quality = 0;

		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.BufferCount = 1;
		scd.OutputWindow = hWnd;
		scd.Windowed = TRUE;
		scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		UINT swapFlags = 0u;
#ifndef NDEBUG
		swapFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		GFX_CHECK_HR(D3D11CreateDeviceAndSwapChain(
			adapters[0].pAdapter,        // Adapter
			D3D_DRIVER_TYPE_UNKNOWN,     // DriverType
			nullptr,                     // Software
			swapFlags,                   // Flags
			nullptr,                     // FeatureLevels
			0,                           // FeatureLevels
			D3D11_SDK_VERSION,           // SDKVersion
			&scd,                        // SwapChainDesc
			swapchain.GetAddressOf(),    // SwapChain
			device.GetAddressOf(),       // Device
			nullptr,                     // FeatureLevel
			deviceContext.GetAddressOf() // ImmediateContext
			));

		com_ptr<ID3D11Texture2D> backBuffer;
		GFX_CHECK_HR(swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf())));

		// Render Target
		GFX_CHECK_HR(device->CreateRenderTargetView(backBuffer.Get(), NULL, renderTargetView.GetAddressOf()));
		//GFX_ERROR_IF_MSG(hr, L"Failed to create RenderTargetView.");

		// Depth
		D3D11_TEXTURE2D_DESC depthStencilDesc = { 0 };
		depthStencilDesc.Width = width;
		depthStencilDesc.Height = height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;
		GFX_CHECK_HR(device->CreateTexture2D(&depthStencilDesc, NULL, depthStencilBuffer.GetAddressOf()));
		GFX_CHECK_HR(device->CreateDepthStencilView(depthStencilBuffer.Get(), NULL, depthStencilView.GetAddressOf()));
		this->deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());

		// Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc = { 0 };
		depthStencilStateDesc.DepthEnable = true;
		depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		GFX_CHECK_HR(device->CreateDepthStencilState(&depthStencilStateDesc, depthStencilState.GetAddressOf()));

		// Rasterizer state
		D3D11_RASTERIZER_DESC rasterizerDesc;
		ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID; // Fill the triangles formed by the vertices. Adjacent vertices are not drawn.
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;  // Do not draw triangles that are back-facing.
		GFX_CHECK_HR(device->CreateRasterizerState(&rasterizerDesc, rasterizerState.GetAddressOf()));

		// Sampler state
		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
		GFX_CHECK_HR(device->CreateSamplerState(&sampDesc, samplerState.GetAddressOf()));

		// viewport
		D3D11_VIEWPORT viewport = { 0 };
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = static_cast<FLOAT>(width);
		viewport.Height = static_cast<FLOAT>(height);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		deviceContext->RSSetViewports(1, &viewport);
	}

	void RendererDX11::PreProcessing()
	{
		float bgcolor[] = { 0.92f, 0.24f, 0.24f, 1.0f };
		deviceContext->ClearRenderTargetView(renderTargetView.Get(), bgcolor);
		deviceContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		deviceContext->OMSetDepthStencilState(depthStencilState.Get(), 0);
		deviceContext->RSSetState(rasterizerState.Get());
		deviceContext->PSSetSamplers(0, 1, samplerState.GetAddressOf());
	}

	void RendererDX11::PostProcessing()
	{
#ifdef IMGUI
		ImGuiUpdate();
#endif // IMGUI

		HRESULT hr;
		GFX_ERROR_INFO;
		if (FAILED(hr = swapchain->Present(1, NULL)))
		{
			if (hr == DXGI_ERROR_DEVICE_REMOVED)
				throw GFX_EXCEPTION_HR(device->GetDeviceRemovedReason());
			else
				throw GFX_EXCEPTION_HR(hr);
		}
	}

	void RendererDX11::SetInputCamera(CameraComponent* cameraComponent)
	{
		if (cameraComponent) inputCamera = cameraComponent;
	}

#ifdef IMGUI
	void RendererDX11::ImGuiSetup(HWND hWnd)
	{
		// Setup ImGui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		const ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplWin32_Init(hWnd);
		ImGui_ImplDX11_Init(device.Get(), deviceContext.Get());
		ImGui::StyleColorsDark();
	}

	void RendererDX11::ImGuiUpdate()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		/*static Transform o1;
		ImGui::Begin("mesh(root)");
		ImGui::DragFloat3("location", o1.location.GetArray());
		ImGui::DragFloat3("rotation", o1.rotation.GetArray());
		ImGui::DragFloat3("scale", o1.scale.GetArray(), 0.1f, 0, 2.0f);
		engine->scene.maps[0]->objects[0]->rootComponent->SetTransform(o1);
		ImGui::End();

		static Transform t1({ 0,5,0 }, { 0,0,90 }, { 1,1,1 });
		ImGui::Begin("mesh(sub)");
		ImGui::DragFloat3("location", t1.location.GetArray());
		ImGui::DragFloat3("rotation", t1.rotation.GetArray());
		ImGui::DragFloat3("scale", t1.scale.GetArray(), 0.1f, 0, 2.0f);
		ImGui::End();
		engine->scene.maps[0]->objects[0]->rootComponent->components[0]->SetTransform(t1);*/

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
#endif // IMGUI
}