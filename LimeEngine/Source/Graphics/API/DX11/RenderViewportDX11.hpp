// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Graphics/RenderViewport.hpp"
#include "RenderAPIDX11.hpp"

namespace LimeEngine
{
	class RenderViewportDX11 : public RenderViewport
	{
	public:
		RenderViewportDX11() = default;
		RenderViewportDX11(uint width, uint height);
		RenderViewportDX11(uint x, uint y, uint width, uint height);

		void Initialize(uint width, uint height);
		void Initialize(uint x, uint y, uint width, uint height);

		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void SetSize(uint width, uint height) override;
		virtual void SetPosition(uint x, uint y) override;

		const CD3D11_VIEWPORT& GetViewport() const;

	public:
		static void BindMyltipleRenderViewports(const std::vector<RenderViewport>& viewports);

	private:
		CD3D11_VIEWPORT viewport{};
	};
}
