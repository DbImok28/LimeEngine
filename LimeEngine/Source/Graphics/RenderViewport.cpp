// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "RenderAPI.hpp"
#include "RenderViewport.hpp"

#if defined(LE_ENABLE_RENDER_API_DX11)
	#include "API/DX11/RenderViewportDX11.hpp"
#endif

namespace LimeEngine
{
	SRef<RenderViewport> RenderViewport::Create(uint width, uint height)
	{
		switch (RenderAPI::DefaultRenderAPI)
		{
			case RenderAPIType::None: break;
#if defined(LE_ENABLE_RENDER_API_DX11)
			case RenderAPIType::DirectX11: return std::make_shared<RenderViewportDX11>(width, height);
#endif
			default: break;
		}
		LE_CORE_ASSERT(false, "Unknown render API. Failed to create RenderViewport");
		return nullptr;
	}
	void RenderViewport::BindMyltipleRenderViewports(const std::vector<RenderViewport>& viewports)
	{
		switch (RenderAPI::DefaultRenderAPI)
		{
			case RenderAPIType::None: break;
#if defined(LE_ENABLE_RENDER_API_DX11)
			case RenderAPIType::DirectX11: return RenderViewportDX11::BindMyltipleRenderViewports(viewports);
#endif
			default: break;
		}
		LE_CORE_ASSERT(false, "Unknown render API. Failed to BindMyltipleRenderViewports");
	}
}
