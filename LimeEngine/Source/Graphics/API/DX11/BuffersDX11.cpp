// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "BuffersDX11.hpp"
#include "ExceptionsDX11.hpp"

namespace LimeEngine
{
	///////////////////////////////////////////////// VertexBufferDX11

	VertexBufferDX11::VertexBufferDX11(const void* vertices, uint count, uint stride, uint offset)
	{
		Initialize(vertices, count, stride, offset);
	}

	void VertexBufferDX11::Initialize(const void* vertices, uint count, uint stride, uint offset)
	{
		this->count = count;
		this->stride = stride;
		this->offset = offset;

		Reset();
		GFX_CHECK_HR_MSG(
			RenderAPI::GetRenderAPI<RenderAPIDX11>().GetContext().TryCreateBuffer(buffer.GetAddressOf(), vertices, stride * count, stride, D3D11_BIND_VERTEX_BUFFER),
			"Failed to initialize vertex buffer");
	}

	void VertexBufferDX11::Reset()
	{
		if (buffer.Get()) buffer.Reset();
	}

	void VertexBufferDX11::Bind() noexcept
	{
		RenderAPI::GetRenderAPI<RenderAPIDX11>().GetContext().SetVertexBuffers(0u, GetAddressOf(), 1u, StridePtr(), &offset);
	}

	ID3D11Buffer* VertexBufferDX11::Get() const noexcept
	{
		return buffer.Get();
	}

	ID3D11Buffer* const* VertexBufferDX11::GetAddressOf() const noexcept
	{
		return buffer.GetAddressOf();
	}

	uint VertexBufferDX11::GetCount() const noexcept
	{
		return count;
	}

	uint VertexBufferDX11::GetStride() const noexcept
	{
		return stride;
	}

	const uint* VertexBufferDX11::StridePtr() const noexcept
	{
		return &stride;
	}

	uint VertexBufferDX11::GetOffset() const noexcept
	{
		return offset;
	}

	///////////////////////////////////////////////// IndexBufferDX11

	IndexBufferDX11::IndexBufferDX11(const uint* indices, uint count)
	{
		Initialize(indices, count);
	}

	void IndexBufferDX11::Initialize(const uint* indices, uint count)
	{
		this->count = count;

		Reset();
		GFX_CHECK_HR_MSG(
			RenderAPI::GetRenderAPI<RenderAPIDX11>().GetContext().TryCreateBuffer(buffer.GetAddressOf(), indices, sizeof(uint) * count, sizeof(uint), D3D11_BIND_INDEX_BUFFER),
			"Failed to initialize index buffer");
	}

	void IndexBufferDX11::Reset()
	{
		if (buffer.Get()) buffer.Reset();
	}

	void IndexBufferDX11::Bind() noexcept
	{
		RenderAPI::GetRenderAPI<RenderAPIDX11>().GetContext().SetIndexBuffer(Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT);
	}

	ID3D11Buffer* IndexBufferDX11::Get() const noexcept
	{
		return buffer.Get();
	}

	ID3D11Buffer* const* IndexBufferDX11::GetAddressOf() const noexcept
	{
		return buffer.GetAddressOf();
	}

	uint IndexBufferDX11::GetCount() const noexcept
	{
		return count;
	}

	///////////////////////////////////////////////// ConstantBufferBaseDX11

	ConstantBufferBaseDX11::ConstantBufferBaseDX11(const void* data, uint dataSize)
	{
		uint bufferSize = static_cast<uint>(dataSize + (16u - (dataSize % 16u)));
		GFX_CHECK_HR_MSG(
			RenderAPI::GetRenderAPI<RenderAPIDX11>().GetContext().TryCreateBuffer(
				buffer.GetAddressOf(), bufferSize, 0u, D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE),
			"Failed to initialize constant buffer");
	}

	void ConstantBufferBaseDX11::ApplyChanges(const void* data, uint dataSize)
	{
		RenderAPI::GetRenderAPI<RenderAPIDX11>().GetContext().RewriteResource(buffer.Get(), 0u, data, dataSize);
	}

	ID3D11Buffer* ConstantBufferBaseDX11::Get() const noexcept
	{
		return buffer.Get();
	}

	ID3D11Buffer* const* ConstantBufferBaseDX11::GetAddressOf() const noexcept
	{
		return buffer.GetAddressOf();
	}

	///////////////////////////////////////////////// VSConstantBufferBaseDX11

	void VSConstantBufferBaseDX11::Bind() noexcept
	{
		RenderAPI::GetRenderAPI<RenderAPIDX11>().GetContext().SetVertexShaderConstantBuffers(0u, GetAddressOf(), 1u);
	}

	void VSConstantBufferBaseDX11::ApplyChanges(const void* data, uint dataSize)
	{
		ConstantBufferBaseDX11::ApplyChanges(data, dataSize);
	}

	///////////////////////////////////////////////// PSConstantBufferBaseDX11

	void PSConstantBufferBaseDX11::Bind() noexcept
	{
		RenderAPI::GetRenderAPI<RenderAPIDX11>().GetContext().SetPixelShaderConstantBuffers(0u, GetAddressOf(), 1u);
	}

	void PSConstantBufferBaseDX11::ApplyChanges(const void* data, uint dataSize)
	{
		ConstantBufferBaseDX11::ApplyChanges(data, dataSize);
	}
}