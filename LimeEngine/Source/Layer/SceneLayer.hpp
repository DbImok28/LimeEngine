// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "EngineLayer.hpp"
#include "Scene/Scene.hpp"

namespace LimeEngine
{
	class SceneLayer : public EngineLayer
	{
		LE_DELETE_COPY(SceneLayer)

	public:
		SceneLayer() noexcept : SceneLayer(MakeUnique<Scene>()) {}
		explicit SceneLayer(URef<Scene>&& scene) noexcept : EngineLayer("SceneLayer"), scene(std::move(scene)) {}

		static SceneLayer& GetSceneLayer();

		virtual void Init() override;
		virtual void Begin() override;
		virtual void End() override;
		virtual void Update() override;
		virtual void DebugUpdate() override;

		Scene* GetScene() noexcept;

	private:
		URef<Scene> scene;
	};
}
