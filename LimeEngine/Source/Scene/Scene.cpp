// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Scene.hpp"
#include "Maps/TestMap.hpp"

namespace LimeEngine
{
	Scene::Scene(Engine* engine) : engine(engine), ScenePrimaryComponent("Scene") {}

	SceneMap* Scene::SetupAttachment(std::unique_ptr<SceneMap>&& map)
	{
		return reinterpret_cast<SceneMap*>(SetupPrimaryAttachment(std::move(map)));
	}

	const std::vector<std::unique_ptr<SceneMap>>& Scene::GetSubMaps() const noexcept
	{
		return reinterpret_cast<const std::vector<std::unique_ptr<SceneMap>>&>(GetSubPrimaryComponents());
	}

	std::string Scene::GetSceneName() const noexcept
	{
		return GetPrimaryName();
	}
}
