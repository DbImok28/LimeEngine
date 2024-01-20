// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "DirectXDef.hpp"
#include "ExceptionsDX11.hpp"
#include "GraphicAdapter.hpp"

namespace LimeEngine
{
	class RenderContextDX11
	{
		LE_DELETE_MOVE_COPY(RenderContextDX11)

	public:
		RenderContextDX11() = default;

		void SetOutputBuffer(ID3D11Texture2D* buffer);

		void CreateDevice();
		void CreateDepthStencil(uint width, uint height);
		void CreateDepthStencilState();
		void CreateRasterizerState();
		void CreateSamplerState();
		void CreateViewport(uint width, uint height);
		void CreateSwapChain(IDXGISwapChain** outSwapchain, void* windowHandle, uint refreshRate) const;

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

		void DestroyRenderTargetView();
		void DestroyDepthStencilView();
		void DestroyDepthStencilBuffer();

		void ClearRenderTargetView(float bgColorRGBA[]);
		void ClearDepthStencilView();

		void MakeWindowAssociation(void* windowHandle);

		void SetRenderTargets();
		void SetTriangleTopology();
		void SetStates();

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

		com_ptr<ID3D11RenderTargetView> renderTargetView = nullptr;

		com_ptr<ID3D11DepthStencilView> depthStencilView = nullptr;
		com_ptr<ID3D11Texture2D> depthStencilBuffer = nullptr;
		com_ptr<ID3D11DepthStencilState> depthStencilState = nullptr;

		com_ptr<ID3D11RasterizerState> rasterizerState = nullptr;

		com_ptr<ID3D11SamplerState> samplerState = nullptr;

		com_ptr<IDXGIFactory> dxgiFactory = nullptr;
		com_ptr<ID3D11Device> device = nullptr;
		com_ptr<ID3D11DeviceContext> deviceContext = nullptr;
	};
}
