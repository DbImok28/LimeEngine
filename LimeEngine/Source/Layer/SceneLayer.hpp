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
		SceneLayer() : SceneLayer(MakeUnique<Scene>()) {}
		SceneLayer(URef<Scene>&& scene) : scene(std::move(scene)) {}
		static SceneLayer& GetSceneLayer();

		void Update() override;
		void DebugUpdate();

		Scene& GetScene() noexcept;

	private:
		URef<Scene> scene;
	};
}
