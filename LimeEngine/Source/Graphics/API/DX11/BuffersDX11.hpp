// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Graphics/Buffers.hpp"
#include "RenderAPIDX11.hpp"

namespace LimeEngine
{
	class VertexBufferDX11 : public VertexBuffer
	{
	public:
		VertexBufferDX11(const void* vertices, uint count, uint stride, uint offset = 0u);

		void Initialize(const void* vertices, uint count, uint stride, uint offset = 0u);
		void Reset();
		virtual void Bind() noexcept override;

		ID3D11Buffer* Get() const noexcept;
		ID3D11Buffer* const* GetAddressOf() const noexcept;
		virtual uint GetCount() const noexcept override;
		uint GetStride() const noexcept;
		const uint* StridePtr() const noexcept;
		uint GetOffset() const noexcept;

	private:
		com_ptr<ID3D11Buffer> buffer;
		uint stride = 0u;
		uint offset = 0u;
	};

	class IndexBufferDX11 : public IndexBuffer
	{
	public:
		IndexBufferDX11(const uint* indices, uint count);

		void Initialize(const uint* indices, uint count);
		void Reset();
		virtual void Bind() noexcept override;

		ID3D11Buffer* Get() const noexcept;
		ID3D11Buffer* const* GetAddressOf() const noexcept;
		virtual uint GetCount() const noexcept override;

	private:
		com_ptr<ID3D11Buffer> buffer;
	};

	class ConstantBufferBaseDX11 : public ConstantBufferBase
	{
	public:
		ConstantBufferBaseDX11(const void* data, uint dataSize);

		virtual void Bind(ShaderType shaderType, uint slotIndex) noexcept override;
		virtual void ApplyChanges(const void* data, uint dataSize) override;

		ID3D11Buffer* Get() const noexcept;
		ID3D11Buffer* const* GetAddressOf() const noexcept;

	private:
		com_ptr<ID3D11Buffer> buffer;
	};
}
