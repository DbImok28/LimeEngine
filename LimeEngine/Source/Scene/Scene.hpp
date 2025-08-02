// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Maps/SceneMap.hpp"
#include "Components/DefaultPlayerCameraComponent.hpp"
#include "System/WorldSubsystem.hpp"

namespace LimeEngine
{
	class Scene : public ScenePrimaryComponent
	{
	public:
		Scene() : ScenePrimaryComponent("Scene") {}

	protected:
		virtual void Init() override;
		virtual void Update() override;

	public:
		SceneMap* SetupAttachment(URef<SceneMap>&& map);
		template <std::derived_from<SceneMap> TMap, typename... TArgs>
		TMap* SetupAttachment(TArgs&&... args) noexcept
		{
			return reinterpret_cast<TMap*>(SetupAttachment(MakeUnique<TMap>(std::forward<TArgs>(args)...)));
		}

		void AddToInitialization(ScenePrimaryComponent* primaryComponent);
		void AddToDestroy(ScenePrimaryComponent* primaryComponent);

	public:
		const std::vector<URef<SceneMap>>& GetSubMaps() const noexcept;
		std::string GetSceneName() const noexcept;

	private:
		std::queue<ScenePrimaryComponent*> componentsWaitingInitialization;
		std::queue<ScenePrimaryComponent*> componentsWaitingBegin;
		std::queue<ScenePrimaryComponent*> componentsWaitingDestroying;

		// TODO: Remove. Engine is global variable
		Engine* engine = nullptr;

		WorldSubsystemHolder subsystemHolder;
	};
}
