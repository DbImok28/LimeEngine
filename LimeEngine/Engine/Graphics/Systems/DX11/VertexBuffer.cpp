#include "VertexBuffer.hpp"
#include <type_traits>

namespace LimeEngine
{
	VertexBuffer::VertexBuffer(const VertexBuffer& vb) noexcept :
		buffer(vb.buffer), bufferSize(vb.bufferSize), stride(vb.stride), offset(vb.offset), deviceContext(vb.deviceContext)
	{}

	VertexBuffer::VertexBuffer(VertexBuffer&& vb) noexcept :
		buffer(std::move(vb.buffer)), bufferSize(std::move(vb.bufferSize)), stride(std::move(vb.stride)), offset(std::move(vb.offset)), deviceContext(std::move(vb.deviceContext))
	{
		vb.buffer = nullptr;
		vb.bufferSize = 0;
		vb.stride = 0;
		vb.offset = 0;
		vb.deviceContext = nullptr;
	}

	VertexBuffer& VertexBuffer::operator=(const VertexBuffer& vb) noexcept
	{
		if (this != &vb)
		{
			buffer = vb.buffer;
			bufferSize = vb.bufferSize;
			stride = vb.stride;
			offset = vb.offset;
			deviceContext = vb.deviceContext;
		}
		return *this;
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vb) noexcept
	{
		if (this != &vb)
		{
			buffer = std::move(vb.buffer);
			bufferSize = std::move(vb.bufferSize);
			stride = std::move(vb.stride);
			offset = std::move(vb.offset);
			deviceContext = std::move(vb.deviceContext);

			vb.buffer = nullptr;
			vb.bufferSize = 0;
			vb.stride = 0;
			offset = 0;
			vb.deviceContext = nullptr;
		}
		return *this;
	}

	HRESULT VertexBuffer::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const Vertex* data, UINT vertexCount, UINT offset) noexcept
	{
		if (!(device && deviceContext)) return E_INVALIDARG;

		if (buffer.Get()) buffer.Reset();
		bufferSize = vertexCount;
		this->offset = offset;
		this->deviceContext = deviceContext;

		D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
		vertexBufferDesc.ByteWidth = stride * vertexCount;
		vertexBufferDesc.StructureByteStride = stride;
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
		vertexBufferData.pSysMem = data;

		return device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, buffer.GetAddressOf());
	}

	void VertexBuffer::Bind() const
	{
		if (deviceContext) deviceContext->IASetVertexBuffers(0, 1, GetAddressOf(), StridePtr(), &offset);
	}

	ID3D11Buffer* VertexBuffer::Get() const noexcept
	{
		return nullptr;
	}

	ID3D11Buffer* const* VertexBuffer::GetAddressOf() const noexcept
	{
		return buffer.GetAddressOf();
	}

	UINT VertexBuffer::VertexCount() const noexcept
	{
		return bufferSize;
	}

	const UINT VertexBuffer::Stride() const noexcept
	{
		return stride;
	}

	const UINT* VertexBuffer::StridePtr() const noexcept
	{
		return &stride;
	}
}