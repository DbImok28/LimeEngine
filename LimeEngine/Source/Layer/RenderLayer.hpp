// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "EngineLayer.hpp"
#include "Graphics/Renderer.hpp"

namespace LimeEngine
{
	class RenderLayer : public EngineLayer
	{
		LE_DELETE_COPY(RenderLayer);

	public:
		RenderLayer(Engine* engine);

		void Update() override;
		void AddToRender(IDrawable* drawable);
		void RemoveFromRender(const IDrawable* drawable) noexcept;

		const CameraComponent* GetRenderCamera() const noexcept;
		void SetRenderCamera(CameraComponent* camera) noexcept;

		const GraphicFactory* GetGraphicFactory() noexcept;
	};
}