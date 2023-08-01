// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "BuffersDX11.hpp"

namespace LimeEngine
{
	IndexBufferDX11::IndexBufferDX11(RendererDX11& renderer) noexcept : BindableDX11(renderer) {}

	HRESULT IndexBufferDX11::Initialize(const std::vector<uint>& indices) noexcept
	{
		bufferSize = static_cast<uint>(indices.size());

		D3D11_BUFFER_DESC indexBufferDesc = { 0 };
		indexBufferDesc.ByteWidth = sizeof(uint) * bufferSize;
		indexBufferDesc.StructureByteStride = sizeof(uint);
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
		indexBufferData.pSysMem = indices.data();

		return GetDevice()->CreateBuffer(&indexBufferDesc, &indexBufferData, buffer.GetAddressOf());
	}

	void IndexBufferDX11::Bind() noexcept
	{
		GetDeviceContext()->IASetIndexBuffer(Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	}

	ID3D11Buffer* IndexBufferDX11::Get() const noexcept
	{
		return buffer.Get();
	}

	ID3D11Buffer* const* IndexBufferDX11::GetAddressOf() const noexcept
	{
		return buffer.GetAddressOf();
	}

	uint IndexBufferDX11::Count() const noexcept
	{
		return bufferSize;
	}
}