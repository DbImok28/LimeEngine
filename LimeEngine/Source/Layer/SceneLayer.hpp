#pragma once
#include "EngineLayer.hpp"
#include "Scene/Scene.hpp"

namespace LimeEngine
{
	class SceneLayer : public EngineLayer
	{
		LE_DELETE_COPY(SceneLayer)

	public:
		explicit SceneLayer(Engine* engine) : SceneLayer(engine, std::make_unique<Scene>(engine)) {}
		SceneLayer(Engine* engine, std::unique_ptr<Scene>&& scene) : EngineLayer(engine), scene(std::move(scene)) {}

		void Update() override;
		void DebugUpdate();

		Scene& GetScene() noexcept;

	private:
		std::unique_ptr<Scene> scene;
	};
}
