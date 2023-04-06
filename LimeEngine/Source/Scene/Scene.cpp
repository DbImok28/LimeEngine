#include "lepch.hpp"
#include "Scene.hpp"
#include "Maps/TestMap.hpp"

namespace LimeEngine
{
	Scene::Scene(Engine* engine) : engine(engine) {}

	void Scene::Update() {}

	void Scene::DebugUpdate() {}

	void Scene::UpdateScene()
	{
		Update();
		for (auto&& map : maps)
		{
			map->UpdateMap();
		}
	}

	void Scene::DebugUpdateScene()
	{
		DebugUpdate();
		for (auto&& map : maps)
		{
			map->DebugUpdateMap();
		}
	}

	void Scene::AttachMap(std::unique_ptr<SceneMap>&& map)
	{
		maps.push_back(std::move(map));
	}
}
