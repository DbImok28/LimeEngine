#include "IndexBuffer.hpp"
#include <type_traits>

namespace LimeEngine
{
	IndexBuffer::IndexBuffer(const IndexBuffer& vb) noexcept : buffer(vb.buffer), bufferSize(vb.bufferSize), deviceContext(vb.deviceContext) {}

	IndexBuffer::IndexBuffer(IndexBuffer&& vb) noexcept : buffer(std::move(vb.buffer)), bufferSize(std::move(vb.bufferSize)), deviceContext(std::move(vb.deviceContext))
	{
		vb.buffer = nullptr;
		vb.bufferSize = 0;
		vb.deviceContext = nullptr;
	}

	IndexBuffer& IndexBuffer::operator=(const IndexBuffer& vb) noexcept
	{
		if (this != &vb)
		{
			buffer = vb.buffer;
			bufferSize = vb.bufferSize;
			deviceContext = vb.deviceContext;
		}
		return *this;
	}

	IndexBuffer& IndexBuffer::operator=(IndexBuffer&& vb) noexcept
	{
		if (this != &vb)
		{
			buffer = std::move(vb.buffer);
			bufferSize = std::move(vb.bufferSize);
			deviceContext = std::move(vb.deviceContext);

			vb.buffer = nullptr;
			vb.bufferSize = 0;
			vb.deviceContext = nullptr;
		}
		return *this;
	}

	HRESULT IndexBuffer::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const uint* data, uint numVertices) noexcept
	{
		if (!(device && deviceContext)) return E_INVALIDARG;

		bufferSize = numVertices;
		this->deviceContext = deviceContext;

		D3D11_BUFFER_DESC indexBufferDesc = { 0 };
		indexBufferDesc.ByteWidth = sizeof(uint) * numVertices;
		indexBufferDesc.StructureByteStride = sizeof(uint);
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
		indexBufferData.pSysMem = data;

		return device->CreateBuffer(&indexBufferDesc, &indexBufferData, buffer.GetAddressOf());
	}
	void IndexBuffer::Bind() const
	{
		if (deviceContext) deviceContext->IASetIndexBuffer(Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
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