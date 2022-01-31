#include "Scene.hpp"
#include "TestMap.hpp"

namespace LimeEngine
{
	Scene::Scene(Engine* engine) : engine(engine) {}

	Scene::Scene(Engine* engine, bool autoLoad)
	{
		if (autoLoad)
		{
			Load();
		}
	}

	void Scene::Load()
	{
		auto map = std::make_unique<TestMap>(engine);
		map->Load();
		AttachMap(std::move(map));
	}

	void Scene::Update()
	{
		//...
	}

	void Scene::Render()
	{
		//...
	}

	void Scene::UpdateScene()
	{
		Update();
		for (auto&& map : maps)
		{
			map->UpdateMap();
		}
	}

	void Scene::RenderScene()
	{
		Render();
		for (auto&& map : maps)
		{
			map->RenderMap();
		}
	}

	void Scene::AttachMap(std::unique_ptr<SceneMap>&& map)
	{
		maps.push_back(std::move(map));
	}

	bool Scene::CameraIsSet() const noexcept
	{
		return activeCamera != nullptr;
	}

	CameraComponent* Scene::GetCamera() const noexcept
	{
		return activeCamera;
	}

	void Scene::SetCamera(CameraComponent* value) noexcept
	{
		activeCamera = value;
	}
}