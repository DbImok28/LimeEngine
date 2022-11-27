#include "Scene.hpp"
#include "TestMap.hpp"

namespace LimeEngine
{
	Scene::Scene(Engine* engine) : engine(engine) {}

	void Scene::Update()
	{
		// ...
	}

	void Scene::UpdateScene()
	{
		Update();
		for (auto&& map : maps)
		{
			map->UpdateMap();
		}
	}

	void Scene::AttachMap(std::unique_ptr<SceneMap>&& map)
	{
		maps.push_back(std::move(map));
	}
}