// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "BindableDX11.hpp"
#include "RendererDX11.hpp"

namespace LimeEngine
{
	ID3D11Device* BindableDX11::GetDevice() const noexcept
	{
		return renderer.context.GetDevice();
	}

	ID3D11DeviceContext* BindableDX11::GetDeviceContext() const noexcept
	{
		return renderer.context.GetDeviceContext();
	}

	RendererDX11& BindableDX11::GetRenderer() const noexcept
	{
		return renderer;
	}

	RenderContextDX11& BindableDX11::GetRenderContext() const noexcept
	{
		return renderer.context;
	}
}
