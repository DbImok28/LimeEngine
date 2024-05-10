// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Buffers.hpp"
#include "RenderAPI.hpp"

#if defined(LE_ENABLE_RENDER_API_DX11)
	#include "API/DX11/BuffersDX11.hpp"
#endif

namespace LimeEngine
{
	std::unique_ptr<VertexBuffer> VertexBuffer::Create(const void* vertices, uint count, uint stride, uint offset)
	{
		switch (RenderAPI::DefaultRenderAPI)
		{
			case RenderAPIType::None: break;
#if defined(LE_ENABLE_RENDER_API_DX11)
			case RenderAPIType::DirectX11: return std::make_unique<VertexBufferDX11>(vertices, count, stride, offset);
#endif
			default: break;
		}
		LE_CORE_ASSERT(false, "Unknown render API. Failed to create VertexBuffer");
		return nullptr;
	}

	std::unique_ptr<IndexBuffer> IndexBuffer::Create(const uint* indices, uint count)
	{
		switch (RenderAPI::DefaultRenderAPI)
		{
			case RenderAPIType::None: break;
#if defined(LE_ENABLE_RENDER_API_DX11)
			case RenderAPIType::DirectX11: return std::make_unique<IndexBufferDX11>(indices, count);
#endif
			default: break;
		}
		LE_CORE_ASSERT(false, "Unknown render API. Failed to create IndexBuffer");
		return nullptr;
	}

	std::unique_ptr<VSConstantBufferBase> VSConstantBufferBase::Create(const void* data, uint dataSize)
	{
		switch (RenderAPI::DefaultRenderAPI)
		{
			case RenderAPIType::None: break;
#if defined(LE_ENABLE_RENDER_API_DX11)
			case RenderAPIType::DirectX11: return std::make_unique<VSConstantBufferBaseDX11>(data, dataSize);
#endif
			default: break;
		}
		LE_CORE_ASSERT(false, "Unknown render API. Failed to create VSConstantBufferBase");
		return nullptr;
	}

	std::unique_ptr<PSConstantBufferBase> PSConstantBufferBase::Create(const void* data, uint dataSize)
	{
		switch (RenderAPI::DefaultRenderAPI)
		{
			case RenderAPIType::None: break;
#if defined(LE_ENABLE_RENDER_API_DX11)
			case RenderAPIType::DirectX11: return std::make_unique<PSConstantBufferBaseDX11>(data, dataSize);
#endif
			default: break;
		}
		LE_CORE_ASSERT(false, "Unknown render API. Failed to create PSConstantBufferBase");
		return nullptr;
	}
}
