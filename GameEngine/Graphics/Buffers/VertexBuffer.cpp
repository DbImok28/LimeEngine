#include "VertexBuffer.hpp"
#include <type_traits>

VertexBuffer::VertexBuffer(const VertexBuffer& vb) noexcept : buffer(vb.buffer), bufferSize(vb.bufferSize){}

VertexBuffer::VertexBuffer(VertexBuffer&& vb) noexcept
	:buffer(std::move(vb.buffer)), bufferSize(std::move(vb.bufferSize))
{
	vb.buffer = nullptr;
	vb.bufferSize = 0;
}

VertexBuffer& VertexBuffer::operator=(const VertexBuffer& vb) noexcept
{
	if (this != &vb)
	{
		buffer = vb.buffer;
		bufferSize = vb.bufferSize;
	}
	return *this;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vb) noexcept
{
	if (this != &vb)
	{
		buffer = std::move(vb.buffer);
		bufferSize = std::move(vb.bufferSize);

		vb.buffer = nullptr;
		vb.bufferSize = 0;
	}
	return *this;
}

HRESULT VertexBuffer::Initialize(ID3D11Device* device, Vertex* data, UINT vertexCount) noexcept
{
	if (buffer.Get() != nullptr)
		buffer.Reset();
	bufferSize = vertexCount;

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