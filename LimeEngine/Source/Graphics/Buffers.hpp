// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "IBindable.hpp"

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

	class ConstantBufferBase : public IBindable
	{
	public:
		virtual ~ConstantBufferBase() = default;
		virtual void ApplyChanges(const void* data, uint dataSize) = 0;
	};

	class VSConstantBufferBase : public ConstantBufferBase
	{
	public:
		template <typename T>
		static std::shared_ptr<VSConstantBufferBase> Create(T* data)
		{
			return Create(data, sizeof(T));
		}
		static std::shared_ptr<VSConstantBufferBase> Create(const void* data, uint dataSize);
	};

	class PSConstantBufferBase : public ConstantBufferBase
	{
	public:
		template <typename T>
		static std::shared_ptr<PSConstantBufferBase> Create(T* data)
		{
			return Create(data, sizeof(T));
		}
		static std::shared_ptr<PSConstantBufferBase> Create(const void* data, uint dataSize);
	};

	// ======================================

	template <typename TBuff, typename T>
	class ConstantBuffer : public IBindable
	{
	public:
		ConstantBuffer() : buff(TBuff::Create(&data, sizeof(T))) {}
		ConstantBuffer(const T& data) : data(data), buff(TBuff::Create(&this->data, sizeof(T))) {}

		virtual void Bind() noexcept override final
		{
			buff->Bind();
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
		std::shared_ptr<TBuff> buff;
	};

	template <typename T>
	using PSConstantBuffer = ConstantBuffer<PSConstantBufferBase, T>;

	template <typename T>
	using VSConstantBuffer = ConstantBuffer<VSConstantBufferBase, T>;
}
