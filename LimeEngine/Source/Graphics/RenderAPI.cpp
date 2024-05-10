// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "RenderAPI.hpp"

#ifdef LE_ENABLE_RENDER_API_DX11
	#include "Graphics/API/DX11/RendererDX11.hpp"
#endif

namespace LimeEngine
{
	std::string RenderAPIToString(RenderAPIType api) noexcept
	{
		switch (api)
		{
			case RenderAPIType::None: return "None";
#ifdef LE_ENABLE_RENDER_API_DX11
			case RenderAPIType::DirectX11: return "DirectX11";
#endif
			default: break;
		}
		LE_CORE_ASSERT(false, "Unknown render API.");
		return "";
	}

#if defined(LE_ENABLE_RENDER_API_DX11)
	RenderAPIType RenderAPI::DefaultRenderAPI = RenderAPIType::DirectX11;
#else
	RenderAPIType RenderAPI::DefaultRenderAPI = RenderAPIType::None;
#endif

	std::unique_ptr<Renderer> RenderAPI::CreateRenderer(RenderAPIType api)
	{
		LE_CORE_LOG_TRACE("Creating a {} renderer", RenderAPIToString(api));
		switch (api)
		{
			case RenderAPIType::None: break;
#if defined(LE_ENABLE_RENDER_API_DX11)
			case RenderAPIType::DirectX11: return std::make_unique<RendererDX11>();
#endif
			default: break;
		}
		LE_CORE_ASSERT(false, "Unknown render API. Failed to create renderer");
		return nullptr;
	}
}
