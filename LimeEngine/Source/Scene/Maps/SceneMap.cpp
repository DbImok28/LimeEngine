// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "SceneMap.hpp"

namespace LimeEngine
{
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
