#pragma once
#include "EngineLayer.hpp"
#include "Scene/Scene.hpp"

namespace LimeEngine
{
	class SceneLayer : public EngineLayer
	{
		LE_DELETE_COPY(SceneLayer)

	public:
		explicit SceneLayer(Engine* engine);

		void Update() override;
		Scene& GetScene() noexcept;

	private:
		Scene scene;
	};
}