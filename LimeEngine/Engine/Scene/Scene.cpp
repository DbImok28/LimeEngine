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
		if (!CameraIsSet())
		{		
			auto cameraObject = std::make_unique<SceneObject>(engine, std::make_unique<DefaultPlayerCameraComponent>(engine)); // auto activated
			maps[0]->AttachObject(std::move(cameraObject));
		}
	}

	void Scene::Update()
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