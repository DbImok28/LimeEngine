// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "Graphics/RenderAPI.hpp"
#include "RenderAPIDX11.hpp"

namespace LimeEngine
{
	RenderAPIType RenderAPIDX11::GetRenderAPIType() const noexcept
	{
		return RenderAPIType::DirectX11;
	}

	std::string LimeEngine::RenderAPIDX11::GetVideoAdapterName() const noexcept
	{
		return context.GetGraphicAdapter().GetName();
	}

	RenderContextDX11& RenderAPIDX11::GetContext() noexcept
	{
		return context;
	}
}
