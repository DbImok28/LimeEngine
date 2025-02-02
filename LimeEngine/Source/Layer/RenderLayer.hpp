// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "EngineLayer.hpp"
#include "Graphics/Renderer.hpp"

namespace LimeEngine
{
	class Renderer;

	class RenderLayer : public EngineLayer
	{
		LE_DELETE_COPY(RenderLayer);

	private:
		static inline const char* LayerType = "RenderLayer";
		static inline std::vector<const char*> LayerDependencies = { "WindowLayer", "SceneLayer", "EditorLayer" };

	public:
		static const std::vector<const char*>& GetLayerDependencies()
		{
			return LayerDependencies;
		}

	public:
		RenderLayer() noexcept : EngineLayer(LayerType) {};
		static RenderLayer* GetRenderLayer();

		virtual void Update() override;
		virtual void DebugUpdate() override;
		void AddToRender(IDrawable* drawable);
		void RemoveFromRender(const IDrawable* drawable);

		const CameraComponent* GetRenderCamera() const noexcept;
		void SetRenderCamera(CameraComponent* camera) noexcept;

	public:
		// TODO: Add render windows
		List<URef<RenderOutput>> renderWindows;
	};
}
