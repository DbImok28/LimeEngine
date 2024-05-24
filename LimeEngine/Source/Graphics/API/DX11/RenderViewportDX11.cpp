// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "RenderViewportDX11.hpp"

namespace LimeEngine
{
	RenderViewportDX11::RenderViewportDX11(uint width, uint height)
	{
		Initialize(width, height);
	}

	RenderViewportDX11::RenderViewportDX11(uint x, uint y, uint width, uint height)
	{
		Initialize(x, y, width, height);
	}

	void RenderViewportDX11::Initialize(uint width, uint height)
	{
		Initialize(0u, 0u, width, height);
	}

	void RenderViewportDX11::Initialize(uint x, uint y, uint width, uint height)
	{
		viewport = CD3D11_VIEWPORT(static_cast<FLOAT>(x), static_cast<FLOAT>(y), static_cast<FLOAT>(width), static_cast<FLOAT>(height));
	}

	void RenderViewportDX11::Bind()
	{
		RenderAPI::GetRenderAPI<RenderAPIDX11>().GetContext().GetDeviceContext()->RSSetViewports(1, &viewport);
	}

	void RenderViewportDX11::Unbind()
	{
		D3D11_VIEWPORT nullViewport = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
		RenderAPI::GetRenderAPI<RenderAPIDX11>().GetContext().GetDeviceContext()->RSSetViewports(1, &nullViewport);
	}

	void RenderViewportDX11::SetSize(uint width, uint height)
	{
		viewport.Width = static_cast<FLOAT>(width);
		viewport.Height = static_cast<FLOAT>(height);
	}

	void RenderViewportDX11::SetPosition(uint x, uint y)
	{
		viewport.TopLeftX = x;
		viewport.TopLeftY = y;
	}

	const CD3D11_VIEWPORT& RenderViewportDX11::GetViewport() const
	{
		return viewport;
	}

	void RenderViewportDX11::BindMyltipleRenderViewports(const std::vector<RenderViewport>& viewports)
	{
		std::vector<CD3D11_VIEWPORT> viewportsDX11;
		viewportsDX11.reserve(viewports.size());
		for (auto& viewport : viewports)
		{
			viewportsDX11.emplace_back(reinterpret_cast<const RenderViewportDX11*>(&viewport)->GetViewport());
		}
		RenderAPI::GetRenderAPI<RenderAPIDX11>().GetContext().GetDeviceContext()->RSSetViewports(viewportsDX11.size(), viewportsDX11.data());
	}
}
