// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "DirectXDef.hpp"
#include "RenderTargetDX11.hpp"
#include "ExceptionsDX11.hpp"
#include "GraphicAdapter.hpp"

namespace LimeEngine
{
	class RenderContextDX11
	{
		LE_DELETE_MOVE_COPY(RenderContextDX11)

	public:
		RenderContextDX11();

		//void SetOutputBuffer(ID3D11Texture2D* buffer);

		void CreateDevice();

		// States

		HRESULT TryCreateDepthStencilState(
			ID3D11DepthStencilState** outDepthStencilState,
			bool depthEnable = true,
			D3D11_DEPTH_WRITE_MASK depthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL,
			D3D11_COMPARISON_FUNC depthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL);
		void CreateDepthStencilState(
			ID3D11DepthStencilState** outDepthStencilState,
			bool depthEnable = true,
			D3D11_DEPTH_WRITE_MASK depthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL,
			D3D11_COMPARISON_FUNC depthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL);
		HRESULT TryCreateRasterizerState(
			ID3D11RasterizerState** outRasterizerState, D3D11_FILL_MODE fillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID, D3D11_CULL_MODE cullMode = D3D11_CULL_MODE::D3D11_CULL_BACK);
		void CreateRasterizerState(
			ID3D11RasterizerState** outRasterizerState, D3D11_FILL_MODE fillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID, D3D11_CULL_MODE cullMode = D3D11_CULL_MODE::D3D11_CULL_BACK);
		HRESULT TryCreateSamplerState(
			ID3D11SamplerState** outSamplerState,
			D3D11_FILTER Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR,
			D3D11_TEXTURE_ADDRESS_MODE AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP,
			D3D11_TEXTURE_ADDRESS_MODE AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP,
			D3D11_TEXTURE_ADDRESS_MODE AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP,
			float MinLOD = 0.0f,
			float MaxLOD = D3D11_FLOAT32_MAX,
			D3D11_COMPARISON_FUNC ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER);
		void CreateSamplerState(
			ID3D11SamplerState** outSamplerState,
			D3D11_FILTER Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR,
			D3D11_TEXTURE_ADDRESS_MODE AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP,
			D3D11_TEXTURE_ADDRESS_MODE AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP,
			D3D11_TEXTURE_ADDRESS_MODE AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP,
			float MinLOD = 0.0f,
			float MaxLOD = D3D11_FLOAT32_MAX,
			D3D11_COMPARISON_FUNC ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER);

		void SetRenderTargets(uint count, ID3D11RenderTargetView* const* renderTargetViews, ID3D11DepthStencilView* depthStencilView) noexcept;

		void SetDepthStencilState(ID3D11DepthStencilState* depthStencilState, uint StencilRef = 0u) noexcept;
		void SetRasterizerState(ID3D11RasterizerState* rasterizerState) noexcept;
		void SetSamplers(uint startSlot, uint count, ID3D11SamplerState* const* samplers) noexcept;

		void ClearRenderTarget(ID3D11RenderTargetView* renderTargetView, const float* clearColor) noexcept;
		void ClearRenderTarget(ID3D11RenderTargetView* renderTargetView) noexcept;
		void ClearDepthStencil(
			ID3D11DepthStencilView* depthStencilView,
			D3D11_CLEAR_FLAG clearFlag = static_cast<D3D11_CLEAR_FLAG>(D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH | D3D11_CLEAR_FLAG::D3D11_CLEAR_STENCIL),
			float clearDepth = 1.0f,
			uint clearStencil = 0u) noexcept;

		void SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology) noexcept;

		// Window

		void MakeWindowAssociation(void* windowHandle);

		void CreateViewport(uint width, uint height);
		void CreateSwapChain(IDXGISwapChain** outSwapchain, void* windowHandle, uint refreshRate) const;

		// Shaders

		void CreateInputLayout(
			const D3D11_INPUT_ELEMENT_DESC* inputDescs, uint inputDescsCount, const void* shaderBuffer, uint shaderBufferSize, ID3D11InputLayout** outInputLoyout) const;
		void CreateVertexShader(const void* shaderBuffer, uint shaderBufferSize, ID3D11VertexShader** outShader) const;
		void CreateVertexShader(
			const D3D11_INPUT_ELEMENT_DESC* inputDescs,
			uint inputDescsCount,
			const void* shaderBuffer,
			uint shaderBufferSize,
			ID3D11InputLayout** outInputLoyout,
			ID3D11VertexShader** outShader) const;
		void CreatePixelShader(const void* shaderBuffer, uint shaderBufferSize, ID3D11PixelShader** outShader) const;

		// Buffers

		HRESULT TryCreateBuffer(
			ID3D11Buffer** outBuffer,
			const void* initData,
			uint byteSize,
			uint stride,
			uint bindFlags,
			D3D11_USAGE usage = D3D11_USAGE_DEFAULT,
			uint CPUAccessFlags = 0u,
			uint miscFlags = 0u) const;
		HRESULT TryCreateBuffer(
			ID3D11Buffer** outBuffer, uint byteSize, uint stride, uint bindFlags, D3D11_USAGE usage = D3D11_USAGE_DEFAULT, uint CPUAccessFlags = 0u, uint miscFlags = 0u) const;
		void CreateBuffer(
			ID3D11Buffer** outBuffer,
			const void* initData,
			uint byteSize,
			uint stride,
			uint bindFlags,
			D3D11_USAGE usage = D3D11_USAGE_DEFAULT,
			uint CPUAccessFlags = 0u,
			uint miscFlags = 0u) const;
		void CreateBuffer(
			ID3D11Buffer** outBuffer, uint byteSize, uint stride, uint bindFlags, D3D11_USAGE usage = D3D11_USAGE_DEFAULT, uint CPUAccessFlags = 0u, uint miscFlags = 0u) const;

		HRESULT TryCreateDepthStencil(uint width, uint height, ID3D11Texture2D** outDepthStencilTexture, ID3D11DepthStencilView** outDepthStencilView);
		void CreateDepthStencil(uint width, uint height, ID3D11Texture2D** depthStencilTexture, ID3D11DepthStencilView** depthStencilView);

		/*HRESULT TryCreateTexture2D(
			uint width,
			uint height,
			uint mipLevels = 1u,
			uint arraySize = 1u,
			DXGI_FORMAT format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM,
			uint sampleCount = 1u,
			uint sampleQuality = 0u,
			D3D11_USAGE usage = D3D11_USAGE::D3D11_USAGE_DEFAULT,
			D3D11_BIND_FLAG bindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE,
			uint CPUAccessFlags = 0u,
			uint miscFlags = 0u)
		{
			D3D11_TEXTURE2D_DESC textureDesc = { 0 };
			textureDesc.Width = width;
			textureDesc.Height = height;
			textureDesc.MipLevels = mipLevels;
			textureDesc.ArraySize = arraySize;
			textureDesc.Format = format;
			textureDesc.SampleDesc.Count = sampleCount;
			textureDesc.SampleDesc.Quality = sampleQuality;
			textureDesc.Usage = usage;
			textureDesc.BindFlags = bindFlags;
			textureDesc.CPUAccessFlags = CPUAccessFlags;
			textureDesc.MiscFlags = miscFlags;

			device->CreateTexture2D(&textureDesc, nullptr, renderTargetTexture.GetAddressOf());
			device->CreateRenderTargetView(renderTargetTexture.Get(), nullptr, renderTargetView.GetAddressOf());
		}

		void CreateTexture2D(uint width, uint height, ID3D11Texture2D** depthStencilTexture, ID3D11DepthStencilView** depthStencilView)
		{
			GFX_CHECK_HR(TryCreateDepthStencil(width, height, depthStencilTexture, depthStencilView));
		}*/

		void SetInputLayout(ID3D11InputLayout* inputLayout);
		void SetVertexShader(ID3D11VertexShader* shader);
		void SetPixelShader(ID3D11PixelShader* shader);
		void SetShaderResources(uint slotIndex, ID3D11ShaderResourceView* const* resources, uint count = 1u);

		void SetIndexBuffer(ID3D11Buffer* buffer, DXGI_FORMAT format, uint offset = 0u);
		void SetVertexBuffers(uint slotIndex, ID3D11Buffer* const* buffers, uint buffersCount, const uint* strides, const uint* offsets);

		void SetVertexShaderConstantBuffers(uint slotIndex, ID3D11Buffer* const* buffers, uint buffersCount);
		void SetPixelShaderConstantBuffers(uint slotIndex, ID3D11Buffer* const* buffers, uint buffersCount);

		HRESULT TryMapResource(ID3D11Resource* resource, uint subresource, D3D11_MAP mapType, uint mapFlags, D3D11_MAPPED_SUBRESOURCE* mappedResource) const;
		void MapResource(ID3D11Resource* resource, uint subresource, D3D11_MAP mapType, uint mapFlags, D3D11_MAPPED_SUBRESOURCE* mappedResource) const;
		void UnmapResource(ID3D11Resource* resource, uint subresource) const;
		void RewriteResource(ID3D11Resource* resource, uint subresource, const void* data, uint dataSize) const;
		template <typename T>
		void RewriteResource(ID3D11Resource* resource, uint subresource, const T& data) const
		{
			RewriteResource(resource, subresource, &data, sizeof(T));
		}

		void DrawIndexed(uint indicesCount, uint offset = 0u);
		void Flush();

	public:
		ID3D11Device* GetDevice() const noexcept;
		ID3D11DeviceContext* GetDeviceContext() const noexcept;

		const GraphicAdapter& GetGraphicAdapter() const noexcept;
		IDXGIFactory* GetDXGIFactory() const noexcept;

	private:
		GraphicAdapter graphicAdapter;

		com_ptr<IDXGIFactory> dxgiFactory = nullptr;
		com_ptr<ID3D11Device> device = nullptr;
		com_ptr<ID3D11DeviceContext> deviceContext = nullptr;
	};
}
