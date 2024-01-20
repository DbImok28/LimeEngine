// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "BuffersDX11.hpp"

namespace LimeEngine
{
	IndexBufferDX11::IndexBufferDX11(RendererDX11& renderer) noexcept : BindableDX11(renderer) {}

	void IndexBufferDX11::Initialize(const std::vector<uint>& indices)
	{
		bufferSize = static_cast<uint>(indices.size());
		GFX_CHECK_HR_MSG(
			GetRenderContext().TryCreateBuffer(buffer.GetAddressOf(), indices.data(), sizeof(uint) * bufferSize, sizeof(uint), D3D11_BIND_INDEX_BUFFER),
			"Failed to initialize index buffer");
	}

	void IndexBufferDX11::Bind() noexcept
	{
		GetRenderContext().SetIndexBuffer(Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT);
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