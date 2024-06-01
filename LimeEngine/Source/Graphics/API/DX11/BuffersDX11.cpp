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

		D3D11_BUFFER_DESC bufferDesc = { 0 };
		bufferDesc.ByteWidth = stride * count;
		bufferDesc.StructureByteStride = stride;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.CPUAccessFlags = 0u;
		bufferDesc.MiscFlags = 0u;

		D3D11_SUBRESOURCE_DATA bufferData = { 0 };
		bufferData.pSysMem = vertices;

		auto device = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDevice();
		GFX_CHECK_HR_MSG(device->CreateBuffer(&bufferDesc, &bufferData, buffer.GetAddressOf()), "Failed to initialize vertex buffer");
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
		D3D11_BUFFER_DESC bufferDesc = { 0 };
		bufferDesc.ByteWidth = sizeof(uint) * count;
		bufferDesc.StructureByteStride = sizeof(uint);
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.CPUAccessFlags = 0u;
		bufferDesc.MiscFlags = 0u;

		D3D11_SUBRESOURCE_DATA bufferData = { 0 };
		bufferData.pSysMem = indices;

		auto device = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDevice();
		GFX_CHECK_HR_MSG(device->CreateBuffer(&bufferDesc, &bufferData, buffer.GetAddressOf()), "Failed to initialize index buffer");
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

		D3D11_BUFFER_DESC bufferDesc = { 0 };
		bufferDesc.ByteWidth = bufferSize;
		bufferDesc.StructureByteStride = 0u;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0u;

		D3D11_SUBRESOURCE_DATA bufferData = { 0 };
		bufferData.pSysMem = data;

		auto device = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDevice();
		GFX_CHECK_HR_MSG(device->CreateBuffer(&bufferDesc, &bufferData, buffer.GetAddressOf()), "Failed to initialize constant buffer");
	}

	void ConstantBufferBaseDX11::Bind(ShaderType shaderType, uint slotIndex) noexcept
	{
		auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();
		switch (shaderType)
		{
			case LimeEngine::ShaderType::VertexShader: deviceContext->VSSetConstantBuffers(slotIndex, 1u, GetAddressOf()); break;
			case LimeEngine::ShaderType::PixelShader: deviceContext->PSSetConstantBuffers(slotIndex, 1u, GetAddressOf()); break;
			default: LE_ASSERT(false, "Failed to bind constant buffer. Invalid shader type"); break;
		}
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
}