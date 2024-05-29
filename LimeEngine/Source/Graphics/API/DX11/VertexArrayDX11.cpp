// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "VertexArrayDX11.hpp"

namespace LimeEngine
{
	void VertexArrayDX11::Bind()
	{
		auto deviceContext = RenderAPI::GetRenderAPI<RenderAPIDX11>().GetDeviceContext();
		deviceContext->IASetVertexBuffers(0u, vertexBuffers.size(), dx11Buffers.data(), strides.data(), offsets.data());
	}

	void VertexArrayDX11::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) noexcept
	{
		this->vertexBuffers.push_back(vertexBuffer);
		auto dx11buffer = reinterpret_cast<VertexBufferDX11*>(vertexBuffer.get());
		if (!dx11buffer)
		{
			LE_CORE_ASSERT(false, "VertexBuffer not initialized");
			return;
		}

		dx11Buffers.push_back(dx11buffer->Get());
		strides.push_back(dx11buffer->GetStride());
		offsets.push_back(dx11buffer->GetOffset());
	}
}
