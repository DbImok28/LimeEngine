// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Maps/SceneMap.hpp"
#include "Components/DefaultPlayerCameraComponent.hpp"

namespace LimeEngine
{
	class Scene : public ScenePrimaryComponent
	{
	public:
		Scene() : ScenePrimaryComponent("Scene") {}

		SceneMap* SetupAttachment(URef<SceneMap>&& map);
		template <std::derived_from<SceneMap> TMap, typename... TArgs>
		TMap* SetupAttachment(TArgs&&... args) noexcept
		{
			return reinterpret_cast<TMap*>(SetupAttachment(MakeUnique<TMap>(std::forward<TArgs>(args)...)));
		}

		const std::vector<URef<SceneMap>>& GetSubMaps() const noexcept;
		std::string GetSceneName() const noexcept;

	private:
		Engine* engine = nullptr;
	};
}
