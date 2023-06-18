#include "lepch.hpp"
#include "RendererDX11.hpp"
#include "Scene/Components/MeshComponent.hpp"
#include "Graphics/Mesh.hpp"
#include "RenderOutputDX11.hpp"

namespace LimeEngine
{
	RendererDX11::RendererDX11(Window& window, DisplayMode mode, bool defaultFullscreenModeIsExclusive) :
		Renderer(std::make_unique<WindowRenderOutputDX11>(*this, window, defaultFullscreenModeIsExclusive)), graphicFactory(*this)
	{
		Init(mode);
		RuntimeEditor::Init(window.GetHandle(), device.Get(), deviceContext.Get());
	}

	RendererDX11::~RendererDX11()
	{
		renderOutput->SetDisplayMode(DisplayMode::Windowed);
		RuntimeEditor::Destroy();
	}

	void RendererDX11::SetOutputBuffer(ID3D11Texture2D* buffer)
	{
		if (buffer == nullptr)
		{
			deviceContext->OMSetRenderTargets(0, nullptr, nullptr);
			return;
		}
		GFX_CHECK_HR(device->CreateRenderTargetView(buffer, nullptr, renderTargetView.GetAddressOf()));
		deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());
	}

	void RendererDX11::Resize(uint width, uint height)
	{
		LE_CORE_LOG_TRACE("Resize renderer(width: {}, height: {})", width, height);
		CreateAllBuffers();
	}

	void RendererDX11::CreateAllBuffers()
	{
		renderOutput->Init();
		CreateDepthStencil();
		renderOutput->Bind();
		CreateDepthStencilState();
		CreateViewport();
	}

	void RendererDX11::DestroyAllBuffers()
	{
		renderTargetView.Reset();
		depthStencilView.Reset();
		depthStencilBuffer.Reset();
		renderOutput->Clear();
		deviceContext->Flush();
	}

	void RendererDX11::Init(DisplayMode mode)
	{
		CreateDevice();
		if (mode == DisplayMode::FullscreenExclusive)
		{
			renderOutput->Init();
			renderOutput->SetDisplayMode(mode);
		}
		else
		{
			CreateAllBuffers();
		}
		CreateRasterizerState();
		CreateSamplerState();
	}

	void RendererDX11::CreateDevice()
	{
		GFX_CHECK_HR_NOINFO(CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(dxgiFactory.GetAddressOf())));

		std::vector<GraphicAdapter> adapters = GraphicAdapter::GetGraphicAdapters(dxgiFactory.Get());
		if (adapters.size() < 1) throw GFX_EXCEPTION_MSG("No found DXGI Adapters.");
		graphicAdapter = adapters[0];

		UINT swapFlags = 0u;
#ifndef NDEBUG
		swapFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		GFX_CHECK_HR(D3D11CreateDevice(
			graphicAdapter.adapter,      // Adapter
			D3D_DRIVER_TYPE_UNKNOWN,     // DriverType
			nullptr,                     // Software
			swapFlags,                   // Flags
			nullptr,                     // FeatureLevels
			0,                           // FeatureLevels
			D3D11_SDK_VERSION,           // SDKVersion
			device.GetAddressOf(),       // Device
			nullptr,                     // FeatureLevel
			deviceContext.GetAddressOf() // ImmediateContext
			));
	}

	void RendererDX11::CreateDepthStencil()
	{
		D3D11_TEXTURE2D_DESC depthStencilDesc = { 0 };
		depthStencilDesc.Width = renderOutput->GetWidth();
		depthStencilDesc.Height = renderOutput->GetHeight();
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
	}

	void RendererDX11::CreateDepthStencilState()
	{
		D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc = { 0 };
		depthStencilStateDesc.DepthEnable = true;
		depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		GFX_CHECK_HR(device->CreateDepthStencilState(&depthStencilStateDesc, depthStencilState.GetAddressOf()));
	}

	void RendererDX11::CreateRasterizerState()
	{
		D3D11_RASTERIZER_DESC rasterizerDesc;
		ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID; // Fill the triangles formed by the vertices. Adjacent vertices are not drawn.
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;  // Do not draw triangles that are back-facing.
		GFX_CHECK_HR(device->CreateRasterizerState(&rasterizerDesc, rasterizerState.GetAddressOf()));
	}

	void RendererDX11::CreateSamplerState()
	{
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
	}

	void RendererDX11::CreateViewport()
	{
		D3D11_VIEWPORT viewport = { 0 };
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = static_cast<FLOAT>(renderOutput->GetWidth());
		viewport.Height = static_cast<FLOAT>(renderOutput->GetHeight());
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		deviceContext->RSSetViewports(1, &viewport);
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

	void RendererDX11::Render()
	{
		if (!camera) return;
		PreProcessing();
		renderQueue.Draw(*this);
		PostProcessing();
	}

	void RendererDX11::PreProcessing()
	{
		float bgcolor[] = { 0.92f, 0.24f, 0.24f, 1.0f };
		deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());
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
		renderOutput->Present();
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

	const GraphicAdapter& RendererDX11::GetGraphicAdapter() const noexcept
	{
		return graphicAdapter;
	}

	IDXGIFactory* RendererDX11::GetDXGIFactory() const noexcept
	{
		return dxgiFactory.Get();
	}
}