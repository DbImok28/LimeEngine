#include "lepch.hpp"
#include "SceneMap.hpp"

namespace LimeEngine
{
	SceneMap::SceneMap(Engine* engine, const std::string& mapName) : engine(engine), ScenePrimaryComponent(mapName) {}

	SceneObject* SceneMap::SetupAttachment(std::unique_ptr<SceneObject>&& object)
	{
		return reinterpret_cast<SceneObject*>(SetupPrimaryAttachment(std::move(object)));
	}

	const std::vector<std::unique_ptr<SceneObject>>& SceneMap::GetSubObjects() const noexcept
	{
		return reinterpret_cast<const std::vector<std::unique_ptr<SceneObject>>&>(GetSubPrimaryComponents());
	}

	std::string SceneMap::GetMapName() const noexcept
	{
		return GetPrimaryName();
	}
}
