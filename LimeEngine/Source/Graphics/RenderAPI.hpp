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
		None = 0,
#ifdef LE_ENABLE_RENDER_API_DX11
		DirectX11 = 1
#endif
	};

	std::string RenderAPIToString(RenderAPIType api) noexcept;

	enum class PrimitiveTopology
	{
		TriangleList
	};

	class RenderAPI
	{
	public:
		static URef<RenderAPI> CreateRendererAPI(RenderAPIType api);

		static void Initialize();

	public:
		virtual void SetPrimitiveTopology(PrimitiveTopology topology) const noexcept = 0;
		virtual void DrawIndexed(uint indicesCount) const = 0;
		virtual void BindPipline() = 0;

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
		static URef<RenderAPI> rendererAPI;
	};
}
