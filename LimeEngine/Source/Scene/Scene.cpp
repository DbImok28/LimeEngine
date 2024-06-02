// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Scene.hpp"
#include "Maps/TestMap.hpp"

namespace LimeEngine
{
	SceneMap* Scene::SetupAttachment(URef<SceneMap>&& map)
	{
		return reinterpret_cast<SceneMap*>(SetupPrimaryAttachment(std::move(map)));
	}

	const std::vector<URef<SceneMap>>& Scene::GetSubMaps() const noexcept
	{
		return reinterpret_cast<const std::vector<URef<SceneMap>>&>(GetSubPrimaryComponents());
	}

	std::string Scene::GetSceneName() const noexcept
	{
		return GetPrimaryName();
	}
}
