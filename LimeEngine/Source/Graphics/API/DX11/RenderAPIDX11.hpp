// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Graphics/RenderAPI.hpp"
#include "RenderContextDX11.hpp"

namespace LimeEngine
{
	class RenderAPIDX11 : public RenderAPI
	{
	public:
		virtual RenderAPIType GetRenderAPIType() const noexcept override;
		virtual std::string GetVideoAdapterName() const noexcept override;

		RenderContextDX11& GetContext() noexcept;

	public:
		RenderContextDX11 context;
	};
}
