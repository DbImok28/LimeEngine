#include "IndexBuffer.hpp"

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

UINT IndexBuffer::BufferSize() const noexcept
{
	return bufferSize;
}