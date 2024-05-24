// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"

namespace LimeEngine
{
	class RenderViewport
	{
	public:
		static std::shared_ptr<RenderViewport> Create(uint width, uint height);
		static void BindMyltipleRenderViewports(const std::vector<RenderViewport>& viewports);

	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetSize(uint width, uint height) = 0;
		virtual void SetPosition(uint x, uint y) = 0;
	};
}
