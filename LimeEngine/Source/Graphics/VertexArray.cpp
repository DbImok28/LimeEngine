// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "RenderAPI.hpp"
#if defined(LE_ENABLE_RENDER_API_DX11)
	#include "API/DX11/VertexArrayDX11.hpp"
#endif

namespace LimeEngine
{
	URef<VertexArray> VertexArray::Create()
	{
		switch (RenderAPI::DefaultRenderAPI)
		{
			case RenderAPIType::None: break;
#if defined(LE_ENABLE_RENDER_API_DX11)
			case RenderAPIType::DirectX11: return MakeUnique<VertexArrayDX11>();
#endif
			default: break;
		}
		LE_ASSERT(false, "Unknown render API. Failed to create VertexShader");
		return nullptr;
	}
}
