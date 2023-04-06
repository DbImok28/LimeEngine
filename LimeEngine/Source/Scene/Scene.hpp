#pragma once
#include "Maps/SceneMap.hpp"
#include "Components/DefaultPlayerCameraComponent.hpp"

namespace LimeEngine
{
	class Scene
	{
	public:
		explicit Scene(Engine* engine);

		void UpdateScene();
		void DebugUpdateScene();

		void AttachMap(std::unique_ptr<SceneMap>&& map);

	private:
		void Update();
		void DebugUpdate();

	public:
		std::vector<std::unique_ptr<SceneMap>> maps;

	private:
		Engine* engine = nullptr;
	};
}
