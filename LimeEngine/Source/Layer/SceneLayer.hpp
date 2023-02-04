#pragma once
#include "EngineLayer.hpp"
#include "Scene/Scene.hpp"

namespace LimeEngine
{
	class SceneLayer : public EngineLayer
	{
	public:
		explicit SceneLayer(Engine* engine);
		SceneLayer(const SceneLayer&) = delete;
		SceneLayer& operator=(const SceneLayer&) = delete;

		void Update() override;
		Scene& GetScene() noexcept;

	private:
		Scene scene;
	};
}