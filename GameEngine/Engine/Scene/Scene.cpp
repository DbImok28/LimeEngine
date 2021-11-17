#include "Scene.hpp"
#include "TestMap.hpp"

void Scene::Initialize(Engine* engine)
{
	this->engine = engine;

	AttachMap(std::make_unique<TestMap>());

	InitializeMaps();
}

void Scene::Update()
{
	UpdateMaps();
}

void Scene::Render()
{
	RenderMaps();
}

void Scene::InitializeMaps()
{
	for (auto&& map : maps)
	{
		map->Initialize(engine);
	}
}

void Scene::UpdateMaps()
{
	for (auto&& map : maps)
	{
		map->Update();
	}
}

void Scene::RenderMaps()
{
	for (auto&& map : maps)
	{
		map->Render();
	}
}

void Scene::AttachMap(std::unique_ptr<SceneMap>&& map)
{
	maps.push_back(std::move(map));
	maps.back()->Initialize(engine);
}