#include "lepch.hpp"
#include "RendererDX11.hpp"
#include "GraphicAdapter.hpp"
#include "Scene/MeshComponent.hpp"
#include "Graphics/Mesh.hpp"
#include "Diagnostics/RuntimeEditor.hpp"

namespace LimeEngine
{
	RendererDX11::RendererDX11(Window* window) : Renderer(window), graphicFactory(*this)
	{
		Initialize(*window);
		RuntimeEditor::Init(window->GetHandle(), device.Get(), deviceContext.Get());
	}

	void RendererDX11::Initialize(const Window& window)
	{
		InitializeDirectX(reinterpret_cast<HWND>(window.GetHandle()), window.GetWidth(), window.GetHeight());
	}

	void RendererDX11::Draw(Mesh& mesh, const TempTransformMatrix& transformMatrix)
	{
		for (auto& segment : mesh.segments)
		{
			if (!(camera && segment.GetMaterial())) return;
			segment.BindRenderData(segment.GetMaterial(), camera, transformMatrix);
			deviceContext->DrawIndexed(segment.IndicesCount(), 0, 0);
		}
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

	void RendererDX11::InitializeDirectX(void* hWnd, int width, int height)
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
		scd.OutputWindow = reinterpret_cast<HWND>(hWnd);
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
		RuntimeEditor::Render();

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
}