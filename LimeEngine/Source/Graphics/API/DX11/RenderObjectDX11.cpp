// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "RenderObjectDX11.hpp"
#include "RendererDX11.hpp"

namespace LimeEngine
{
	ID3D11Device* RenderObjectDX11::GetDevice() const noexcept
	{
		return renderer.context.GetDevice();
	}

	ID3D11DeviceContext* RenderObjectDX11::GetDeviceContext() const noexcept
	{
		return renderer.context.GetDeviceContext();
	}

	RendererDX11& RenderObjectDX11::GetRenderer() const noexcept
	{
		return renderer;
	}

	RenderContextDX11& RenderObjectDX11::GetRenderContext() const noexcept
	{
		return renderer.context;
	}
}
