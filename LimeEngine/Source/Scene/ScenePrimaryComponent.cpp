// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "ScenePrimaryComponent.hpp"
#include "Layer/SceneLayer.hpp"

namespace LimeEngine
{
	ScenePrimaryComponent::~ScenePrimaryComponent() noexcept
	{
		if (primaryComponentState == SceneComponentState::Started || primaryComponentState == SceneComponentState::WaitForEnd)
		{
			LE_WARNING(false, "Incorrect destruction of the component {}. Call Destroy to correctly destroy the component", GetPrimaryName());
			DestroyImmediately();
		}
	}

	const std::vector<URef<ScenePrimaryComponent>>& ScenePrimaryComponent::GetSubPrimaryComponents() const noexcept
	{
		return subPrimaryComponent;
	}

	ScenePrimaryComponent* ScenePrimaryComponent::SetupPrimaryAttachment(URef<ScenePrimaryComponent>&& component) noexcept
	{
		ScenePrimaryComponent* attachedComponent = subPrimaryComponent.emplace_back(std::move(component)).get();
		attachedComponent->primaryOwner = this;

		GetScene()->AddToInitialization(attachedComponent);
		return attachedComponent;
	}

	URef<ScenePrimaryComponent> ScenePrimaryComponent::PrimaryDetach(ScenePrimaryComponent* component) noexcept
	{
		auto foundComponentIter = std::find_if(std::begin(subPrimaryComponent), std::end(subPrimaryComponent), [component](auto& item) { return item.get() == component; });

		LE_ASSERT(foundComponentIter != std::end(subPrimaryComponent), "Owner does not have a child component {}", component->GetPrimaryName());
		if (foundComponentIter == std::end(subPrimaryComponent)) return nullptr;

		auto&& foundComponent = std::move(*foundComponentIter);
		subPrimaryComponent.erase(foundComponentIter);

		return std::move(foundComponent);
	}

	void ScenePrimaryComponent::PrimaryDetachDestroy(ScenePrimaryComponent* component) noexcept
	{
		auto foundComponentIter = std::find_if(std::begin(subPrimaryComponent), std::end(subPrimaryComponent), [component](auto& item) { return item.get() == component; });

		LE_ASSERT(foundComponentIter != std::end(subPrimaryComponent), "Owner does not have a child component {}", component->GetPrimaryName());
		subPrimaryComponent.erase(foundComponentIter);
	}

	URef<ScenePrimaryComponent> ScenePrimaryComponent::PrimaryDetach() noexcept
	{
		LE_ASSERT(primaryOwner, "Cannot detach component because component has no owner");
		return primaryOwner->PrimaryDetach(this);
	}

	void ScenePrimaryComponent::PrimaryDetachDestroy() noexcept
	{
		if (primaryOwner) primaryOwner->PrimaryDetachDestroy(this);
	}

	void ScenePrimaryComponent::PropagateUpdate()
	{
		if (primaryComponentState != SceneComponentState::Started) return;

		Update();
		for (auto&& component : subPrimaryComponent)
		{
			component->PropagateUpdate();
		}
	}

	void ScenePrimaryComponent::PropagateDebugUpdate()
	{
		if (primaryComponentState != SceneComponentState::Started) return;

		DebugUpdate();
		for (auto&& component : subPrimaryComponent)
		{
			component->PropagateDebugUpdate();
		}
	}

	void ScenePrimaryComponent::PropagateInit()
	{
		if (primaryComponentState != SceneComponentState::WaitForInit) return;

		for (auto&& component : subPrimaryComponent)
		{
			component->PropagateInit();
		}

		Init();
		primaryComponentState = SceneComponentState::WaitForBegin;
	}

	void ScenePrimaryComponent::PropagateBegin()
	{
		if (primaryComponentState != SceneComponentState::WaitForBegin) return;

		Begin();
		primaryComponentState = SceneComponentState::Started;

		for (auto&& component : subPrimaryComponent)
		{
			component->PropagateBegin();
		}
	}

	void ScenePrimaryComponent::PropagateEnd()
	{
		End();
		primaryComponentState = SceneComponentState::WaitForDestroy;
		for (auto&& component : subPrimaryComponent)
		{
			component->PropagateEnd();
		}
	}

	void ScenePrimaryComponent::Destroy()
	{
		primaryComponentState = SceneComponentState::WaitForEnd;
		GetScene()->AddToDestroy(this);
	}

	void ScenePrimaryComponent::DestroyImmediately()
	{
		PropagateEnd();
		primaryComponentState = SceneComponentState::WaitForDestroy;
		PrimaryDetachDestroy();
	}

	Scene* ScenePrimaryComponent::GetScene() const noexcept
	{
		return SceneLayer::GetSceneLayer()->GetScene();
	}

	const std::string& ScenePrimaryComponent::GetPrimaryName() const noexcept
	{
		return primaryName;
	}
}
