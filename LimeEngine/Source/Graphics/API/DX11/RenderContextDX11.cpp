// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "RenderContextDX11.hpp"

namespace LimeEngine
{
	void RenderContextDX11::SetOutputBuffer(ID3D11Texture2D* buffer)
	{
		if (buffer == nullptr)
		{
			deviceContext->OMSetRenderTargets(0, nullptr, nullptr);
			return;
		}
		GFX_CHECK_HR(device->CreateRenderTargetView(buffer, nullptr, renderTargetView.GetAddressOf()));
		deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());
	}

	void RenderContextDX11::CreateDevice()
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
			0u,                          // FeatureLevels
			D3D11_SDK_VERSION,           // SDKVersion
			device.GetAddressOf(),       // Device
			nullptr,                     // FeatureLevel
			deviceContext.GetAddressOf() // ImmediateContext
			));
	}

	void RenderContextDX11::CreateDepthStencil(uint width, uint height)
	{
		D3D11_TEXTURE2D_DESC depthStencilDesc = { 0 };
		depthStencilDesc.Width = width;
		depthStencilDesc.Height = height;
		depthStencilDesc.MipLevels = 1u;
		depthStencilDesc.ArraySize = 1u;
		depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1u;
		depthStencilDesc.SampleDesc.Quality = 0u;
		depthStencilDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0u;
		depthStencilDesc.MiscFlags = 0u;
		GFX_CHECK_HR(device->CreateTexture2D(&depthStencilDesc, NULL, depthStencilBuffer.GetAddressOf()));
		GFX_CHECK_HR(device->CreateDepthStencilView(depthStencilBuffer.Get(), NULL, depthStencilView.GetAddressOf()));
	}

	void RenderContextDX11::CreateDepthStencilState()
	{
		D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc = { 0 };
		depthStencilStateDesc.DepthEnable = true;
		depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		GFX_CHECK_HR(device->CreateDepthStencilState(&depthStencilStateDesc, depthStencilState.GetAddressOf()));
	}

	void RenderContextDX11::CreateRasterizerState()
	{
		D3D11_RASTERIZER_DESC rasterizerDesc;
		ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID; // Fill the triangles formed by the vertices. Adjacent vertices are not drawn.
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;  // Do not draw triangles that are back-facing.
		GFX_CHECK_HR(device->CreateRasterizerState(&rasterizerDesc, rasterizerState.GetAddressOf()));
	}

	void RenderContextDX11::CreateSamplerState()
	{
		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0.0f;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
		GFX_CHECK_HR(device->CreateSamplerState(&sampDesc, samplerState.GetAddressOf()));
	}

	void RenderContextDX11::CreateViewport(uint width, uint height)
	{
		D3D11_VIEWPORT viewport = { 0 };
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = static_cast<FLOAT>(width);
		viewport.Height = static_cast<FLOAT>(height);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		deviceContext->RSSetViewports(1, &viewport);
	}

	void RenderContextDX11::CreateSwapChain(IDXGISwapChain** outSwapchain, void* windowHandle, uint refreshRate)
	{
		DXGI_SWAP_CHAIN_DESC scd = { 0 };
		scd.Windowed = TRUE;
		scd.BufferDesc.RefreshRate.Numerator = refreshRate;
		scd.BufferDesc.RefreshRate.Denominator = 1u;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		scd.SampleDesc.Count = 1u;
		scd.SampleDesc.Quality = 0u;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.BufferCount = 1u;
		scd.OutputWindow = reinterpret_cast<HWND>(windowHandle);
		scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		GFX_CHECK_HR(dxgiFactory->CreateSwapChain(device.Get(), &scd, outSwapchain));
	}

	void RenderContextDX11::CreateInputLayout(
		const D3D11_INPUT_ELEMENT_DESC* inputDescs, uint inputDescsCount, const void* shaderBuffer, uint shaderBufferSize, ID3D11InputLayout** outInputLoyout)
	{
		GFX_CHECK_HR(device->CreateInputLayout(inputDescs, inputDescsCount, shaderBuffer, shaderBufferSize, outInputLoyout));
	}

	void RenderContextDX11::CreateVertexShader(const void* shaderBuffer, uint shaderBufferSize, ID3D11VertexShader** outShader)
	{
		GFX_CHECK_HR(device->CreateVertexShader(shaderBuffer, shaderBufferSize, NULL, outShader));
	}

	void RenderContextDX11::CreateVertexShader(
		const D3D11_INPUT_ELEMENT_DESC* inputDescs,
		uint inputDescsCount,
		const void* shaderBuffer,
		uint shaderBufferSize,
		ID3D11InputLayout** outInputLoyout,
		ID3D11VertexShader** outShader)
	{
		CreateInputLayout(inputDescs, inputDescsCount, shaderBuffer, shaderBufferSize, outInputLoyout);
		CreateVertexShader(shaderBuffer, shaderBufferSize, outShader);
	}

	void RenderContextDX11::CreatePixelShader(const void* shaderBuffer, uint shaderBufferSize, ID3D11PixelShader** outShader)
	{
		GFX_CHECK_HR(device->CreatePixelShader(shaderBuffer, shaderBufferSize, NULL, outShader));
	}

	void RenderContextDX11::DestroyRenderTargetView()
	{
		renderTargetView.Reset();
	}

	void RenderContextDX11::DestroyDepthStencilView()
	{
		depthStencilView.Reset();
	}

	void RenderContextDX11::DestroyDepthStencilBuffer()
	{
		depthStencilBuffer.Reset();
	}

	void RenderContextDX11::ClearRenderTargetView(float bgColorRGBA[])
	{
		deviceContext->ClearRenderTargetView(renderTargetView.Get(), bgColorRGBA);
	}

	void RenderContextDX11::ClearDepthStencilView()
	{
		deviceContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0u);
	}

	void RenderContextDX11::MakeWindowAssociation(void* windowHandle)
	{
		GFX_CHECK_HR(dxgiFactory->MakeWindowAssociation(reinterpret_cast<HWND>(windowHandle), DXGI_MWA_NO_WINDOW_CHANGES));
	}

	void RenderContextDX11::SetRenderTargets()
	{
		deviceContext->OMSetRenderTargets(1u, renderTargetView.GetAddressOf(), depthStencilView.Get());
	}

	void RenderContextDX11::SetTriangleTopology()
	{
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void RenderContextDX11::SetStates()
	{
		deviceContext->OMSetDepthStencilState(depthStencilState.Get(), 0u);
		deviceContext->RSSetState(rasterizerState.Get());
		deviceContext->PSSetSamplers(0u, 1u, samplerState.GetAddressOf());
	}

	void RenderContextDX11::SetInputLayout(ID3D11InputLayout* inputLayout)
	{
		deviceContext->IASetInputLayout(inputLayout);
	}

	void RenderContextDX11::SetVertexShader(ID3D11VertexShader* shader)
	{
		deviceContext->VSSetShader(shader, NULL, 0u);
	}

	void RenderContextDX11::SetPixelShader(ID3D11PixelShader* shader)
	{
		deviceContext->PSSetShader(shader, NULL, 0u);
	}

	void RenderContextDX11::SetShaderResources(uint slotIndex, ID3D11ShaderResourceView* const* resources, uint count)
	{
		deviceContext->PSSetShaderResources(slotIndex, count, resources);
	}

	void RenderContextDX11::DrawIndexed(uint indicesCount, uint offset)
	{
		deviceContext->DrawIndexed(indicesCount, offset, 0);
	}

	void RenderContextDX11::Flush()
	{
		deviceContext->Flush();
	}

	ID3D11Device* RenderContextDX11::GetDevice() const noexcept
	{
		return device.Get();
	}

	ID3D11DeviceContext* RenderContextDX11::GetDeviceContext() const noexcept
	{
		return deviceContext.Get();
	}

	const GraphicAdapter& RenderContextDX11::GetGraphicAdapter() const noexcept
	{
		return graphicAdapter;
	}

	IDXGIFactory* RenderContextDX11::GetDXGIFactory() const noexcept
	{
		return dxgiFactory.Get();
	}
}
