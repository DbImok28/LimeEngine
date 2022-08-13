#pragma once
#include "../../../CoreBase.hpp"
#include "../../../Exceptions/GraphicsExceptions.hpp"
#include "BindableDX11.hpp"

namespace LimeEngine
{
	template <typename T>
	class VertexBuffer : public BindableDX11
	{
	public:
		VertexBuffer(RenderingSystemDX11& renderingSystem) noexcept : BindableDX11(renderingSystem) {}
		virtual ~VertexBuffer() override = default;

		HRESULT Initialize(const std::vector<T>& vertices, uint offset = 0u) noexcept
		{
			if (buffer.Get()) buffer.Reset();
			bufferSize = static_cast<uint>(vertices.size());
			this->offset = offset;

			D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
			vertexBufferDesc.ByteWidth = stride * bufferSize;
			vertexBufferDesc.StructureByteStride = stride;
			vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vertexBufferDesc.CPUAccessFlags = 0u;
			vertexBufferDesc.MiscFlags = 0u;

			D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
			vertexBufferData.pSysMem = vertices.data();

			return GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexBufferData, buffer.GetAddressOf());
		}
		virtual void Bind() noexcept override
		{
			GetDeviceContext()->IASetVertexBuffers(0u, 1u, GetAddressOf(), StridePtr(), &offset);
		}
		ID3D11Buffer* Get() const noexcept
		{
			return nullptr;
		}
		ID3D11Buffer* const* GetAddressOf() const noexcept
		{
			return buffer.GetAddressOf();
		}
		uint VertexCount() const noexcept
		{
			return bufferSize;
		}
		const uint Stride() const noexcept
		{
			return stride;
		}
		const uint* StridePtr() const noexcept
		{
			return &stride;
		}

	public:
		uint offset = 0u;

	private:
		com_ptr<ID3D11Buffer> buffer;
		uint stride = sizeof(T);
		uint bufferSize = 0u;
	};

	class IndexBuffer : public BindableDX11
	{
	public:
		IndexBuffer(RenderingSystemDX11& renderingSystem) noexcept;
		virtual ~IndexBuffer() override = default;

		HRESULT Initialize(const std::vector<uint>& indices) noexcept;
		virtual void Bind() noexcept override;
		ID3D11Buffer* Get() const noexcept;
		ID3D11Buffer* const* GetAddressOf() const noexcept;
		uint Count() const noexcept;

	private:
		com_ptr<ID3D11Buffer> buffer;
		uint bufferSize = 0u;
	};

	template <typename T>
	class ConstantBuffer : public BindableDX11
	{
	public:
		ConstantBuffer(RenderingSystemDX11& renderer) noexcept : BindableDX11(renderer), data{} {}
		virtual ~ConstantBuffer() override = default;

		HRESULT Initialize() noexcept
		{
			D3D11_BUFFER_DESC desc = { 0 };
			desc.Usage = D3D11_USAGE_DYNAMIC;
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			desc.MiscFlags = 0;
			desc.ByteWidth = static_cast<uint>(sizeof(T) + (16 - (sizeof(T) % 16)));
			desc.StructureByteStride = 0;

			return GetDevice()->CreateBuffer(&desc, 0, buffer.GetAddressOf());
		}
		void ApplyChanges()
		{
			D3D11_MAPPED_SUBRESOURCE mappedResorce;
			HRESULT hr = GetDeviceContext()->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResorce);
			GFX_CHECK_HR_MSG(hr, "Failed to map constant buffer.");

			CopyMemory(mappedResorce.pData, &data, sizeof(T));
			GetDeviceContext()->Unmap(buffer.Get(), 0);
		}
		ID3D11Buffer* Get() const noexcept
		{
			return buffer.Get();
		}
		ID3D11Buffer* const* GetAddressOf() const noexcept
		{
			return buffer.GetAddressOf();
		}

	public:
		T data;

	private:
		com_ptr<ID3D11Buffer> buffer;
	};

	template <typename T>
	class VertexShaderConstantBuffer : public ConstantBuffer<T>
	{
	public:
		using ConstantBuffer<T>::GetAddressOf;
		using ConstantBuffer<T>::GetDeviceContext;
		using ConstantBuffer<T>::ConstantBuffer;

		virtual void Bind() noexcept override
		{
			GetDeviceContext()->VSSetConstantBuffers(0, 1, GetAddressOf());
		}
	};

	template <typename T>
	class PixelShaderConstantBuffer : public ConstantBuffer<T>
	{
	public:
		using ConstantBuffer<T>::GetAddressOf;
		using ConstantBuffer<T>::GetDeviceContext;
		using ConstantBuffer<T>::ConstantBuffer;

		virtual void Bind() noexcept override
		{
			GetDeviceContext()->PSSetConstantBuffers(0, 1, GetAddressOf());
		}
	};
}