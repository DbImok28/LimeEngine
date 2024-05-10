// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "DirectXDef.hpp"
#include "RendererDX11.hpp"

namespace LimeEngine
{
	class RenderObjectDX11
	{
	public:
		explicit RenderObjectDX11(RendererDX11& renderer) : renderer(renderer) {}

	protected:
		ID3D11Device* GetDevice() const noexcept;
		ID3D11DeviceContext* GetDeviceContext() const noexcept;
		RendererDX11& GetRenderer() const noexcept;
		RenderContextDX11& GetRenderContext() const noexcept;

	private:
		RendererDX11& renderer;
	};
}
