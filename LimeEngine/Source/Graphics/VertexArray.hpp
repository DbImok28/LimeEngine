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
		static std::unique_ptr<VertexArray> Create();

	public:
		virtual ~VertexArray() = default;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) noexcept
		{
			this->vertexBuffers.push_back(vertexBuffer);
		}
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) noexcept
		{
			this->indexBuffer = indexBuffer;
		}

		const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() noexcept
		{
			return vertexBuffers;
		}
		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() noexcept
		{
			return indexBuffer;
		}
		uint IndicesCount() noexcept
		{
			return indexBuffer->GetCount();
		}

	protected:
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
		std::shared_ptr<IndexBuffer> indexBuffer;
	};
}
