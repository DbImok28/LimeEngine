// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "ExceptionsDX11.hpp"
#include "BindableDX11.hpp"

namespace LimeEngine
{
	template <typename T>
	class VertexBufferDX11 : public BindableDX11
	{
	public:
		explicit VertexBufferDX11(RendererDX11& renderer) noexcept : BindableDX11(renderer) {}

		void Initialize(const std::vector<T>& vertices, uint offset = 0u)
		{
			if (buffer.Get()) buffer.Reset();
			bufferSize = static_cast<uint>(vertices.size());
			this->offset = offset;

			GFX_CHECK_HR_MSG(
				GetRenderContext().TryCreateBuffer(buffer.GetAddressOf(), vertices.data(), stride * bufferSize, stride, D3D11_BIND_VERTEX_BUFFER),
				"Failed to initialize vertex buffer");
		}
		virtual void Bind() noexcept override
		{
			GetRenderContext().SetVertexBuffers(0u, GetAddressOf(), 1u, StridePtr(), &offset);
		}
		ID3D11Buffer* Get() const noexcept
		{
			return buffer.Get();
		}
		ID3D11Buffer* const* GetAddressOf() const noexcept
		{
			return buffer.GetAddressOf();
		}
		uint VertexCount() const noexcept
		{
			return bufferSize;
		}
		uint Stride() const noexcept
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

	class IndexBufferDX11 : public BindableDX11
	{
	public:
		explicit IndexBufferDX11(RendererDX11& renderer) noexcept;

		void Initialize(const std::vector<uint>& indices);
		virtual void Bind() noexcept override;
		ID3D11Buffer* Get() const noexcept;
		ID3D11Buffer* const* GetAddressOf() const noexcept;
		uint Count() const noexcept;

	private:
		com_ptr<ID3D11Buffer> buffer;
		uint bufferSize = 0u;
	};

	template <typename T>
	class ConstantBufferDX11 : public BindableDX11
	{
	public:
		explicit ConstantBufferDX11(RendererDX11& renderer) noexcept : BindableDX11(renderer), data{} {}

		void Initialize()
		{
			uint bufferSize = static_cast<uint>(sizeof(T) + (16 - (sizeof(T) % 16)));
			GFX_CHECK_HR_MSG(
				GetRenderContext().TryCreateBuffer(buffer.GetAddressOf(), bufferSize, 0u, D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE),
				"Failed to initialize constant buffer");
		}
		void ApplyChanges()
		{
			GetRenderContext().RewriteResource(buffer.Get(), 0u, data);
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
	class VertexShaderConstantBufferDX11 : public ConstantBufferDX11<T>
	{
	public:
		using ConstantBufferDX11<T>::GetAddressOf;
		using ConstantBufferDX11<T>::GetRenderContext;
		using ConstantBufferDX11<T>::ConstantBufferDX11;

		virtual void Bind() noexcept override
		{
			GetRenderContext().SetVertexShaderConstantBuffers(0u, GetAddressOf(), 1u);
		}
	};

	template <typename T>
	class PixelShaderConstantBufferDX11 : public ConstantBufferDX11<T>
	{
	public:
		using ConstantBufferDX11<T>::GetAddressOf;
		using ConstantBufferDX11<T>::GetRenderContext;
		using ConstantBufferDX11<T>::ConstantBufferDX11;

		virtual void Bind() noexcept override
		{
			GetRenderContext().SetPixelShaderConstantBuffers(0u, GetAddressOf(), 1u);
		}
	};
}
