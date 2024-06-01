// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "IBindable.hpp"
#include "Shaders.hpp"

namespace LimeEngine
{
	class VertexBuffer : public IBindable
	{
	public:
		template <typename T>
		static std::shared_ptr<VertexBuffer> Create(const std::vector<T>& vertices, uint offset = 0u)
		{
			return Create(vertices.data(), vertices.size(), sizeof(T), offset);
		}
		template <typename T>
		static std::shared_ptr<VertexBuffer> Create(T* vertices, uint count, uint offset = 0u)
		{
			return Create(vertices, count, sizeof(T), offset);
		}
		static std::shared_ptr<VertexBuffer> Create(const void* vertices, uint count, uint stride, uint offset = 0u);

	public:
		virtual ~VertexBuffer() = default;

		virtual uint GetCount() const noexcept
		{
			return count;
		}

	protected:
		uint count = 0u;
	};

	class IndexBuffer : public IBindable
	{
	public:
		static std::shared_ptr<IndexBuffer> Create(const std::vector<uint>& indices)
		{
			return Create(indices.data(), indices.size());
		}
		static std::shared_ptr<IndexBuffer> Create(const uint* indices, uint count);

	public:
		virtual ~IndexBuffer() = default;

		virtual uint GetCount() const noexcept
		{
			return count;
		}

	protected:
		uint count = 0u;
	};

	// ======================================

	class ConstantBufferBase
	{
	public:
		template <typename T>
		static std::unique_ptr<ConstantBufferBase> Create(T* data)
		{
			return Create(data, sizeof(T));
		}
		static std::unique_ptr<ConstantBufferBase> Create(const void* data, uint dataSize);

		virtual ~ConstantBufferBase() = default;

		virtual void Bind(ShaderType shaderType, uint slotIndex) noexcept = 0;
		virtual void ApplyChanges(const void* data, uint dataSize) = 0;
	};

	template <typename T>
	class ConstantBuffer
	{
	public:
		ConstantBuffer() : buff(ConstantBufferBase::Create(&data, sizeof(T))) {}
		ConstantBuffer(const T& data) : data(data), buff(ConstantBufferBase::Create(&this->data, sizeof(T))) {}

		void Bind(ShaderType shaderType, uint slotIndex) noexcept
		{
			buff->Bind(shaderType, slotIndex);
		}
		void ApplyChanges()
		{
			buff->ApplyChanges(&data, sizeof(T));
		}
		void Set(const T& data)
		{
			this->data = data;
			ApplyChanges();
		}

	public:
		T data{};
		std::shared_ptr<ConstantBufferBase> buff;
	};
}
