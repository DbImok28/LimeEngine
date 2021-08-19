#include "IndexBuffer.hpp"
#include <type_traits>

IndexBuffer::IndexBuffer(const IndexBuffer& vb) noexcept
	: buffer(vb.buffer), bufferSize(vb.bufferSize) {}

IndexBuffer::IndexBuffer(IndexBuffer&& vb) noexcept
	:buffer(std::move(vb.buffer)), bufferSize(std::move(vb.bufferSize))
{
	vb.buffer = nullptr;
	vb.bufferSize = 0;
}

IndexBuffer& IndexBuffer::operator=(const IndexBuffer& vb) noexcept
{
	if (this != &vb)
	{
		buffer = vb.buffer;
		bufferSize = vb.bufferSize;
	}
	return *this;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& vb) noexcept
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

HRESULT IndexBuffer::Initialize(ID3D11Device* device, DWORD* data, UINT numVertices) noexcept
{
	bufferSize = numVertices;

	D3D11_BUFFER_DESC indexBufferDesc = { 0 };
	indexBufferDesc.ByteWidth = sizeof(DWORD) * numVertices;
	indexBufferDesc.StructureByteStride = sizeof(DWORD);
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
	indexBufferData.pSysMem = data;

	return device->CreateBuffer(&indexBufferDesc, &indexBufferData, buffer.GetAddressOf());
}
ID3D11Buffer* IndexBuffer::Get() const noexcept
{
	return buffer.Get();
}

ID3D11Buffer* const* IndexBuffer::GetAddressOf() const noexcept
{
	return buffer.GetAddressOf();
}

UINT IndexBuffer::Count() const noexcept
{
	return bufferSize;
}