#include "SceneMap.hpp"

namespace LimeEngine
{
	void SceneMap::Initialize(Engine* engine)
	{
		this->engine = engine;
		InitializeObjects();
	}

	void SceneMap::Update()
	{
		UpdateObjects();
	}

	void SceneMap::Render()
	{
		RenderObjects();
	}

	void SceneMap::InitializeObjects()
	{
		for (auto&& object : objects)
		{
			object->Initialize(engine);
		}
	}

	void SceneMap::UpdateObjects()
	{
		for (auto&& object : objects)
		{
			object->Update();
		}
	}

	void SceneMap::RenderObjects()
	{
		for (auto&& object : objects)
		{
			object->Render();
		}
	}

	void SceneMap::AttachObject(std::unique_ptr<SceneObject>&& object)
	{
		objects.push_back(std::move(object));
		objects.back()->Initialize(engine);
	}
}