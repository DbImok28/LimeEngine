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
	public:
		static std::unique_ptr<Renderer> CreateRenderer(RenderAPIType api);
		static std::unique_ptr<RenderAPI> CreateRendererAPI(RenderAPIType api);

		static void Initialize();

	public:
		virtual RenderAPIType GetRenderAPIType() const noexcept = 0;
		virtual std::string GetVideoAdapterName() const noexcept = 0;

	public:
		inline static RenderAPI& GetRenderAPI() noexcept
		{
			return *rendererAPI.get();
		}
		template <std::derived_from<RenderAPI> T>
		inline static T& GetRenderAPI() noexcept
		{
			return *reinterpret_cast<T*>(rendererAPI.get());
		}

	public:
		static RenderAPIType DefaultRenderAPI;

	private:
		static std::unique_ptr<RenderAPI> rendererAPI;
	};
}
