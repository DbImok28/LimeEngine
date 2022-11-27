#pragma once
#include "SceneMap.hpp"
#include "DefaultPlayerCameraComponent.hpp"

namespace LimeEngine
{
	class Scene
	{
	public:
		explicit Scene(Engine* engine);
		void UpdateScene();
		void AttachMap(std::unique_ptr<SceneMap>&& map);

	private:
		void Update();

	public:
		std::vector<std::unique_ptr<SceneMap>> maps;

	private:
		Engine* engine = nullptr;
	};
}