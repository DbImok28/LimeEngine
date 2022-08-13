#include "Buffers.hpp"

namespace LimeEngine
{
	IndexBuffer::IndexBuffer(RenderingSystemDX11& renderingSystem) noexcept : BindableDX11(renderingSystem) {}

	HRESULT IndexBuffer::Initialize(const std::vector<uint>& indices) noexcept
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

	void IndexBuffer::Bind() noexcept
	{
		GetDeviceContext()->IASetIndexBuffer(Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	}

	ID3D11Buffer* IndexBuffer::Get() const noexcept
	{
		return buffer.Get();
	}

	ID3D11Buffer* const* IndexBuffer::GetAddressOf() const noexcept
	{
		return buffer.GetAddressOf();
	}

	uint IndexBuffer::Count() const noexcept
	{
		return bufferSize;
	}
}