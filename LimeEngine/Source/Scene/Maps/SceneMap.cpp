#include "lepch.hpp"
#include "SceneMap.hpp"

namespace LimeEngine
{
	SceneMap::SceneMap(Engine* engine) : engine(engine) {}

	void SceneMap::Update() {}

	void SceneMap::DebugUpdate() {}

	void SceneMap::UpdateMap()
	{
		Update();
		for (auto&& object : objects)
		{
			object->UpdateObject();
		}
	}

	void SceneMap::DebugUpdateMap()
	{
		DebugUpdate();
		for (auto&& object : objects)
		{
			object->DebugUpdateObject();
		}
	}

	void SceneMap::Load() {}

	void SceneMap::AttachObject(std::unique_ptr<SceneObject>&& object)
	{
		objects.push_back(std::move(object));
	}
}
