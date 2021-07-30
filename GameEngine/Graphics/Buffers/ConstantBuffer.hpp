#pragma once
#include "../Exceptions/GraphicsExceptions.hpp"

template<class T>
class ConstantBuffer
{
public:
	ConstantBuffer(const ConstantBuffer&) = delete;
	ConstantBuffer(ConstantBuffer&& cb) noexcept = delete;
	ConstantBuffer& operator=(const ConstantBuffer&) = delete;
	ConstantBuffer& operator=(ConstantBuffer&& cb) noexcept = delete;


	ConstantBuffer() {}
	HRESULT Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
	{
		this->deviceContext = deviceContext;

		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.ByteWidth = static_cast<UINT>(sizeof(T) + (16 - (sizeof(T) % 16)));
		desc.StructureByteStride = 0;

		return device->CreateBuffer(&desc, 0, buffer.GetAddressOf());
	}
	void ApplyChanges()
	{
		D3D11_MAPPED_SUBRESOURCE mappedResorce;
		HRESULT hr = deviceContext->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResorce);
		GFX_ERROR_IF(hr, L"Failed to map constant buffer.");

		CopyMemory(mappedResorce.pData, &data, sizeof(T));
		deviceContext->Unmap(buffer.Get(), 0);
	}

	ID3D11Buffer* Get() const noexcept
	{
		return buffer.Get();
	}
	ID3D11Buffer* const* GetAddressOf() const noexcept
	{
		return buffer.GetAddressOf();
	}
private:
	com_ptr<ID3D11Buffer> buffer;
	ID3D11DeviceContext* deviceContext = nullptr;
public:
	T data;
};

struct CB_VS_VertexShader
{
	float xOffset = 0;
	float yOffset = 0;
};