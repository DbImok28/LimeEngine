// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "RenderContextDX11.hpp"

namespace LimeEngine
{
	RenderContextDX11::RenderContextDX11()
	{
		CreateDevice();
	}

	void RenderContextDX11::CreateDevice()
	{
		GFX_CHECK_HR(CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(dxgiFactory.GetAddressOf())));

		std::vector<GraphicAdapter> adapters = GraphicAdapter::GetGraphicAdapters(dxgiFactory.Get());
		if (adapters.size() < 1) throw GFX_EXCEPTION_MSG("No found DXGI Adapters.");
		graphicAdapter = adapters[0];

		UINT flags = 0u;
#ifndef NDEBUG
		flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		GFX_CHECK_HR(D3D11CreateDevice(
			graphicAdapter.adapter,      // Adapter
			D3D_DRIVER_TYPE_UNKNOWN,     // DriverType
			nullptr,                     // Software
			flags,                       // Flags
			nullptr,                     // FeatureLevels
			0u,                          // FeatureLevels
			D3D11_SDK_VERSION,           // SDKVersion
			device.GetAddressOf(),       // Device
			nullptr,                     // FeatureLevel
			deviceContext.GetAddressOf() // ImmediateContext
			));
	}

	HRESULT RenderContextDX11::TryCreateDepthStencilState(
		ID3D11DepthStencilState** outDepthStencilState, bool depthEnable, D3D11_DEPTH_WRITE_MASK depthWriteMask, D3D11_COMPARISON_FUNC depthFunc)
	{
		D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc = { 0 };
		depthStencilStateDesc.DepthEnable = depthEnable;
		depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		return device->CreateDepthStencilState(&depthStencilStateDesc, outDepthStencilState);
	}

	void RenderContextDX11::CreateDepthStencilState(
		ID3D11DepthStencilState** outDepthStencilState, bool depthEnable, D3D11_DEPTH_WRITE_MASK depthWriteMask, D3D11_COMPARISON_FUNC depthFunc)
	{
		GFX_CHECK_HR(TryCreateDepthStencilState(outDepthStencilState, depthEnable, depthWriteMask, depthFunc));
	}

	HRESULT RenderContextDX11::TryCreateRasterizerState(ID3D11RasterizerState** outRasterizerState, D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode)
	{
		D3D11_RASTERIZER_DESC rasterizerDesc;
		ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
		rasterizerDesc.FillMode = fillMode;
		rasterizerDesc.CullMode = cullMode;
		GFX_CHECK_HR(device->CreateRasterizerState(&rasterizerDesc, outRasterizerState));
	}

	void RenderContextDX11::CreateRasterizerState(ID3D11RasterizerState** outRasterizerState, D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode)
	{
		GFX_CHECK_HR(TryCreateRasterizerState(outRasterizerState, fillMode, cullMode));
	}

	HRESULT RenderContextDX11::TryCreateSamplerState(
		ID3D11SamplerState** outSamplerState,
		D3D11_FILTER Filter,
		D3D11_TEXTURE_ADDRESS_MODE AddressU,
		D3D11_TEXTURE_ADDRESS_MODE AddressV,
		D3D11_TEXTURE_ADDRESS_MODE AddressW,
		float MinLOD,
		float MaxLOD,
		D3D11_COMPARISON_FUNC ComparisonFunc)
	{
		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = Filter;
		sampDesc.AddressU = AddressU;
		sampDesc.AddressV = AddressV;
		sampDesc.AddressW = AddressW;
		sampDesc.ComparisonFunc = ComparisonFunc;
		sampDesc.MinLOD = MinLOD;
		sampDesc.MaxLOD = MaxLOD;
		return device->CreateSamplerState(&sampDesc, outSamplerState);
	}

	void RenderContextDX11::CreateSamplerState(
		ID3D11SamplerState** outSamplerState,
		D3D11_FILTER Filter,
		D3D11_TEXTURE_ADDRESS_MODE AddressU,
		D3D11_TEXTURE_ADDRESS_MODE AddressV,
		D3D11_TEXTURE_ADDRESS_MODE AddressW,
		float MinLOD,
		float MaxLOD,
		D3D11_COMPARISON_FUNC ComparisonFunc)
	{
		GFX_CHECK_HR(TryCreateSamplerState(outSamplerState, Filter, AddressU, AddressV, AddressW, MinLOD, MaxLOD, ComparisonFunc));
	}

	void RenderContextDX11::SetRenderTargets(uint count, ID3D11RenderTargetView* const* renderTargetViews, ID3D11DepthStencilView* depthStencilView) noexcept
	{
		deviceContext->OMSetRenderTargets(count, renderTargetViews, depthStencilView);
	}

	void RenderContextDX11::SetDepthStencilState(ID3D11DepthStencilState* depthStencilState, uint StencilRef) noexcept
	{
		deviceContext->OMSetDepthStencilState(depthStencilState, StencilRef);
	}

	void RenderContextDX11::SetRasterizerState(ID3D11RasterizerState* rasterizerState) noexcept
	{
		deviceContext->RSSetState(rasterizerState);
	}

	void RenderContextDX11::SetSamplers(uint startSlot, uint count, ID3D11SamplerState* const* samplers) noexcept
	{
		deviceContext->PSSetSamplers(startSlot, count, samplers);
	}

	void RenderContextDX11::ClearRenderTarget(ID3D11RenderTargetView* renderTargetView, const float* clearColor) noexcept
	{
		deviceContext->ClearRenderTargetView(renderTargetView, clearColor);
	}

	void RenderContextDX11::ClearRenderTarget(ID3D11RenderTargetView* renderTargetView) noexcept
	{
		float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		deviceContext->ClearRenderTargetView(renderTargetView, clearColor);
	}

	void RenderContextDX11::ClearDepthStencil(ID3D11DepthStencilView* depthStencilView, D3D11_CLEAR_FLAG clearFlag, float clearDepth, uint clearStencil) noexcept
	{
		deviceContext->ClearDepthStencilView(depthStencilView, clearFlag, clearDepth, clearStencil);
	}

	void RenderContextDX11::SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology) noexcept
	{
		deviceContext->IASetPrimitiveTopology(topology);
	}

	void RenderContextDX11::MakeWindowAssociation(void* windowHandle)
	{
		GFX_CHECK_HR(dxgiFactory->MakeWindowAssociation(reinterpret_cast<HWND>(windowHandle), DXGI_MWA_NO_WINDOW_CHANGES));
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

	void RenderContextDX11::CreateSwapChain(IDXGISwapChain** outSwapchain, void* windowHandle, uint refreshRate) const
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
		const D3D11_INPUT_ELEMENT_DESC* inputDescs, uint inputDescsCount, const void* shaderBuffer, uint shaderBufferSize, ID3D11InputLayout** outInputLoyout) const
	{
		GFX_CHECK_HR(device->CreateInputLayout(inputDescs, inputDescsCount, shaderBuffer, shaderBufferSize, outInputLoyout));
	}

	void RenderContextDX11::CreateVertexShader(const void* shaderBuffer, uint shaderBufferSize, ID3D11VertexShader** outShader) const
	{
		GFX_CHECK_HR(device->CreateVertexShader(shaderBuffer, shaderBufferSize, NULL, outShader));
	}

	void RenderContextDX11::CreateVertexShader(
		const D3D11_INPUT_ELEMENT_DESC* inputDescs,
		uint inputDescsCount,
		const void* shaderBuffer,
		uint shaderBufferSize,
		ID3D11InputLayout** outInputLoyout,
		ID3D11VertexShader** outShader) const
	{
		CreateInputLayout(inputDescs, inputDescsCount, shaderBuffer, shaderBufferSize, outInputLoyout);
		CreateVertexShader(shaderBuffer, shaderBufferSize, outShader);
	}

	void RenderContextDX11::CreatePixelShader(const void* shaderBuffer, uint shaderBufferSize, ID3D11PixelShader** outShader) const
	{
		GFX_CHECK_HR(device->CreatePixelShader(shaderBuffer, shaderBufferSize, NULL, outShader));
	}

	HRESULT RenderContextDX11::TryCreateBuffer(
		ID3D11Buffer** outBuffer, const void* initData, uint byteSize, uint stride, uint bindFlags, D3D11_USAGE usage, uint CPUAccessFlags, uint miscFlags) const
	{
		D3D11_BUFFER_DESC indexBufferDesc = { 0 };
		indexBufferDesc.ByteWidth = byteSize;
		indexBufferDesc.StructureByteStride = stride;
		indexBufferDesc.Usage = usage;
		indexBufferDesc.BindFlags = bindFlags;
		indexBufferDesc.CPUAccessFlags = CPUAccessFlags;
		indexBufferDesc.MiscFlags = miscFlags;

		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
		indexBufferData.pSysMem = initData;

		return device->CreateBuffer(&indexBufferDesc, &indexBufferData, outBuffer);
	}

	HRESULT RenderContextDX11::TryCreateBuffer(ID3D11Buffer** outBuffer, uint byteSize, uint stride, uint bindFlags, D3D11_USAGE usage, uint CPUAccessFlags, uint miscFlags) const
	{
		D3D11_BUFFER_DESC indexBufferDesc = { 0 };
		indexBufferDesc.ByteWidth = byteSize;
		indexBufferDesc.StructureByteStride = stride;
		indexBufferDesc.Usage = usage;
		indexBufferDesc.BindFlags = bindFlags;
		indexBufferDesc.CPUAccessFlags = CPUAccessFlags;
		indexBufferDesc.MiscFlags = miscFlags;

		return device->CreateBuffer(&indexBufferDesc, nullptr, outBuffer);
	}

	void RenderContextDX11::CreateBuffer(
		ID3D11Buffer** outBuffer, const void* initData, uint byteSize, uint stride, uint bindFlags, D3D11_USAGE usage, uint CPUAccessFlags, uint miscFlags) const
	{
		GFX_CHECK_HR(TryCreateBuffer(outBuffer, initData, byteSize, stride, bindFlags, usage, CPUAccessFlags, miscFlags));
	}

	void RenderContextDX11::CreateBuffer(ID3D11Buffer** outBuffer, uint byteSize, uint stride, uint bindFlags, D3D11_USAGE usage, uint CPUAccessFlags, uint miscFlags) const
	{
		GFX_CHECK_HR(TryCreateBuffer(outBuffer, byteSize, stride, bindFlags, usage, CPUAccessFlags, miscFlags));
	}

	HRESULT RenderContextDX11::TryCreateDepthStencil(uint width, uint height, ID3D11Texture2D** outDepthStencilTexture, ID3D11DepthStencilView** outDepthStencilView)
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

		HRESULT hr = device->CreateTexture2D(&depthStencilDesc, NULL, outDepthStencilTexture);
		if (FAILED(hr)) return hr;

		hr = device->CreateDepthStencilView(*outDepthStencilTexture, NULL, outDepthStencilView);
		if (FAILED(hr)) (*outDepthStencilTexture)->Release();

		return hr;
	}

	void RenderContextDX11::CreateDepthStencil(uint width, uint height, ID3D11Texture2D** depthStencilTexture, ID3D11DepthStencilView** depthStencilView)
	{
		GFX_CHECK_HR(TryCreateDepthStencil(width, height, depthStencilTexture, depthStencilView));
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

	void RenderContextDX11::SetIndexBuffer(ID3D11Buffer* buffer, DXGI_FORMAT format, uint offset)
	{
		deviceContext->IASetIndexBuffer(buffer, format, offset);
	}

	void RenderContextDX11::SetVertexBuffers(uint slotIndex, ID3D11Buffer* const* buffers, uint buffersCount, const uint* strides, const uint* offsets)
	{
		deviceContext->IASetVertexBuffers(slotIndex, buffersCount, buffers, strides, offsets);
	}

	void RenderContextDX11::SetVertexShaderConstantBuffers(uint slotIndex, ID3D11Buffer* const* buffers, uint buffersCount)
	{
		deviceContext->VSSetConstantBuffers(slotIndex, buffersCount, buffers);
	}

	void RenderContextDX11::SetPixelShaderConstantBuffers(uint slotIndex, ID3D11Buffer* const* buffers, uint buffersCount)
	{
		deviceContext->PSSetConstantBuffers(slotIndex, buffersCount, buffers);
	}

	HRESULT RenderContextDX11::TryMapResource(ID3D11Resource* resource, uint subresource, D3D11_MAP mapType, uint mapFlags, D3D11_MAPPED_SUBRESOURCE* mappedResource) const
	{
		return deviceContext->Map(resource, subresource, mapType, mapFlags, mappedResource);
	}

	void RenderContextDX11::MapResource(ID3D11Resource* resource, uint subresource, D3D11_MAP mapType, uint mapFlags, D3D11_MAPPED_SUBRESOURCE* mappedResource) const
	{
		GFX_CHECK_HR(TryMapResource(resource, subresource, mapType, mapFlags, mappedResource));
	}

	void RenderContextDX11::UnmapResource(ID3D11Resource* resource, uint subresource) const
	{
		deviceContext->Unmap(resource, subresource);
	}

	void RenderContextDX11::RewriteResource(ID3D11Resource* resource, uint subresource, const void* data, uint dataSize) const
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		MapResource(resource, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

		CopyMemory(mappedResource.pData, data, dataSize);
		UnmapResource(resource, 0);
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
