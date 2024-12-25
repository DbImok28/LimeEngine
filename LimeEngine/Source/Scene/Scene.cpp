// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Scene.hpp"
#include "Maps/TestMap.hpp"

namespace LimeEngine
{
	void Scene::Update()
	{
		ScenePrimaryComponent::Update();

		while (!componentsWaitingInitialization.empty())
		{
			auto component = componentsWaitingInitialization.front();
			componentsWaitingInitialization.pop();

			componentsWaitingBegin.emplace(component);

			component->PropagateInit();
		}

		while (!componentsWaitingBegin.empty())
		{
			auto component = componentsWaitingBegin.front();
			componentsWaitingBegin.pop();

			component->PropagateBegin();
		}

		while (!componentsWaitingDestroying.empty())
		{
			auto component = componentsWaitingDestroying.front();
			componentsWaitingDestroying.pop();

			component->PropagateEnd();
			component->PrimaryDetachDestroy();
		}
	}

	SceneMap* Scene::SetupAttachment(URef<SceneMap>&& map)
	{
		return reinterpret_cast<SceneMap*>(SetupPrimaryAttachment(std::move(map)));
	}

	void Scene::AddToInitialization(ScenePrimaryComponent* primaryComponent)
	{
		if (primaryComponent->primaryComponentState == SceneComponentState::WaitForInit)
		{
			if (primaryComponent->primaryOwner && primaryComponent->primaryOwner->primaryComponentState == SceneComponentState::WaitForInit) return;
			componentsWaitingInitialization.emplace(primaryComponent);
		}
		else if (primaryComponent->primaryComponentState == SceneComponentState::WaitForBegin)
		{
			if (primaryComponent->primaryOwner && primaryComponent->primaryOwner->primaryComponentState == SceneComponentState::WaitForBegin) return;
			componentsWaitingBegin.emplace(primaryComponent);
		}
	}

	void Scene::AddToDestroy(ScenePrimaryComponent* primaryComponent)
	{
		primaryComponentState = SceneComponentState::WaitForEnd;

		if (primaryComponent->primaryOwner && primaryComponent->primaryOwner->primaryComponentState == SceneComponentState::WaitForEnd) return;
		componentsWaitingDestroying.emplace(primaryComponent);
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
