// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Graphics/Buffers.hpp"
#include "RendererDX11.hpp"

namespace LimeEngine
{
	class VertexBufferDX11 : public VertexBuffer
	{
	public:
		VertexBufferDX11(const void* vertices, uint count, uint stride, uint offset = 0u);

		virtual void Bind() noexcept override;
		ID3D11Buffer* Get() const noexcept;
		ID3D11Buffer* const* GetAddressOf() const noexcept;
		uint VertexCount() const noexcept;
		uint Stride() const noexcept;
		const uint* StridePtr() const noexcept;

	public:
		uint offset = 0u;

	private:
		com_ptr<ID3D11Buffer> buffer;
		uint stride = 0u;
		uint count = 0u;
	};

	class IndexBufferDX11 : public IndexBuffer
	{
	public:
		IndexBufferDX11(const uint* indices, uint count);

		void Bind() noexcept;
		ID3D11Buffer* Get() const noexcept;
		ID3D11Buffer* const* GetAddressOf() const noexcept;
		uint Count() const noexcept;

	private:
		com_ptr<ID3D11Buffer> buffer;
		uint count = 0u;
	};

	class ConstantBufferBaseDX11
	{
	public:
		ConstantBufferBaseDX11(const void* data, uint dataSize);

		void ApplyChanges(const void* data, uint dataSize);
		ID3D11Buffer* Get() const noexcept;
		ID3D11Buffer* const* GetAddressOf() const noexcept;

	private:
		com_ptr<ID3D11Buffer> buffer;
	};

	class VSConstantBufferBaseDX11 : public ConstantBufferBaseDX11, public VSConstantBufferBase
	{
	public:
		using ConstantBufferBaseDX11::ConstantBufferBaseDX11;

		virtual void Bind() noexcept override;
		virtual void ApplyChanges(const void* data, uint dataSize) override;
	};

	class PSConstantBufferBaseDX11 : public ConstantBufferBaseDX11, public PSConstantBufferBase
	{
	public:
		using ConstantBufferBaseDX11::ConstantBufferBaseDX11;

		virtual void Bind() noexcept override;
		virtual void ApplyChanges(const void* data, uint dataSize) override;
	};
}
