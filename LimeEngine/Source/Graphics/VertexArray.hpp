// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Graphics/Buffers.hpp"

namespace LimeEngine
{
	class VertexArray : public IBindable
	{
	public:
		static URef<VertexArray> Create();

	public:
		virtual ~VertexArray() = default;

		virtual void AddVertexBuffer(const SRef<VertexBuffer>& vertexBuffer) noexcept
		{
			this->vertexBuffers.push_back(vertexBuffer);
		}
		virtual void SetIndexBuffer(const SRef<IndexBuffer>& indexBuffer) noexcept
		{
			this->indexBuffer = indexBuffer;
		}

		const std::vector<SRef<VertexBuffer>>& GetVertexBuffer() noexcept
		{
			return vertexBuffers;
		}
		const SRef<IndexBuffer>& GetIndexBuffer() noexcept
		{
			return indexBuffer;
		}
		uint IndicesCount() noexcept
		{
			return indexBuffer->GetCount();
		}

	protected:
		std::vector<SRef<VertexBuffer>> vertexBuffers;
		SRef<IndexBuffer> indexBuffer;
	};
}
