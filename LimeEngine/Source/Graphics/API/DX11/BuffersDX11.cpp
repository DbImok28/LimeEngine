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

		D3D11_BUFFER_DESC indexBufferDesc = { 0 };
		indexBufferDesc.ByteWidth = stride * count;
		indexBufferDesc.StructureByteStride = stride;
		indexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.CPUAccessFlags = 0u;
		indexBufferDesc.MiscFlags = 0u;

		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
		indexBufferData.pSysMem = vertices;

		auto device = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDevice();
		GFX_CHECK_HR_MSG(device->CreateBuffer(&indexBufferDesc, &indexBufferData, buffer.GetAddressOf()), "Failed to initialize vertex buffer");
	}

	void VertexBufferDX11::Reset()
	{
		if (buffer.Get()) buffer.Reset();
	}

	void VertexBufferDX11::Bind() noexcept
	{
		auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();
		deviceContext->IASetVertexBuffers(0u, 1u, GetAddressOf(), StridePtr(), &offset);
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
		D3D11_BUFFER_DESC indexBufferDesc = { 0 };
		indexBufferDesc.ByteWidth = sizeof(uint) * count;
		indexBufferDesc.StructureByteStride = sizeof(uint);
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.CPUAccessFlags = 0u;
		indexBufferDesc.MiscFlags = 0u;

		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
		indexBufferData.pSysMem = indices;

		auto device = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDevice();
		GFX_CHECK_HR_MSG(device->CreateBuffer(&indexBufferDesc, &indexBufferData, buffer.GetAddressOf()), "Failed to initialize vertex buffer");
	}

	void IndexBufferDX11::Reset()
	{
		if (buffer.Get()) buffer.Reset();
	}

	void IndexBufferDX11::Bind() noexcept
	{
		auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();
		deviceContext->IASetIndexBuffer(Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0u);
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

		D3D11_BUFFER_DESC indexBufferDesc = { 0 };
		indexBufferDesc.ByteWidth = bufferSize;
		indexBufferDesc.StructureByteStride = 0u;
		indexBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		indexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		indexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		indexBufferDesc.MiscFlags = 0u;

		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
		indexBufferData.pSysMem = data;

		auto device = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDevice();
		GFX_CHECK_HR_MSG(device->CreateBuffer(&indexBufferDesc, &indexBufferData, buffer.GetAddressOf()), "Failed to initialize constant buffer");
	}

	void ConstantBufferBaseDX11::ApplyChanges(const void* data, uint dataSize)
	{
		auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		GFX_CHECK_HR_MSG(deviceContext->Map(buffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &mappedResource), "Failed to map constant buffer.");
		CopyMemory(mappedResource.pData, data, dataSize);
		deviceContext->Unmap(buffer.Get(), 0u);
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
		auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();
		deviceContext->VSSetConstantBuffers(0u, 1u, GetAddressOf());
	}

	void VSConstantBufferBaseDX11::ApplyChanges(const void* data, uint dataSize)
	{
		ConstantBufferBaseDX11::ApplyChanges(data, dataSize);
	}

	///////////////////////////////////////////////// PSConstantBufferBaseDX11

	void PSConstantBufferBaseDX11::Bind() noexcept
	{
		auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();
		deviceContext->PSSetConstantBuffers(0u, 1u, GetAddressOf());
	}

	void PSConstantBufferBaseDX11::ApplyChanges(const void* data, uint dataSize)
	{
		ConstantBufferBaseDX11::ApplyChanges(data, dataSize);
	}
}