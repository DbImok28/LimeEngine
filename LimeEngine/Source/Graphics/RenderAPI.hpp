// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Renderer.hpp"

namespace LimeEngine
{
	enum class RenderAPIType
	{
		None,
#ifdef LE_ENABLE_RENDER_API_DX11
		DirectX11
#endif
	};

	std::string RenderAPIToString(RenderAPIType api) noexcept;

	class RenderAPI
	{
		RenderAPI() = delete;

	public:
		static std::unique_ptr<Renderer> CreateRenderer(RenderAPIType api);

		static RenderAPIType DefaultRenderAPI;
	};
}
