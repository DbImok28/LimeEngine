// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "VertexArrayDX11.hpp"
#include "RendererDX11.hpp"

namespace LimeEngine
{
	void VertexArrayDX11::Bind()
	{
		Renderer::GetRenderer<RendererDX11>().context.SetVertexBuffers(0u, dx11Buffers.data(), vertexBuffers.size(), strides.data(), offsets.data());
	}

	void VertexArrayDX11::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) noexcept
	{
		this->vertexBuffers.push_back(vertexBuffer);
		auto dx11buffer = reinterpret_cast<VertexBufferDX11*>(vertexBuffer.get());
		LE_CORE_ASSERT(dx11buffer, "VertexBuffer not initialized");
		dx11Buffers.push_back(dx11buffer->Get());
		strides.push_back(dx11buffer->GetStride());
		offsets.push_back(dx11buffer->GetOffset());
	}
}
