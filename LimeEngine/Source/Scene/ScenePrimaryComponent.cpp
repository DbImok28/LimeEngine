// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "ScenePrimaryComponent.hpp"

namespace LimeEngine
{
	const std::string& ScenePrimaryComponent::GetPrimaryName() const noexcept
	{
		return primaryName;
	}

	const std::vector<URef<ScenePrimaryComponent>>& ScenePrimaryComponent::GetSubPrimaryComponents() const noexcept
	{
		return subPrimaryComponent;
	}

	ScenePrimaryComponent* ScenePrimaryComponent::SetupPrimaryAttachment(URef<ScenePrimaryComponent>&& component) noexcept
	{
		subPrimaryComponent.push_back(std::move(component));
		return subPrimaryComponent.back().get();
	}

	void ScenePrimaryComponent::UpdateSubPrimaryComponents()
	{
		Update();
		for (auto&& component : subPrimaryComponent)
		{
			component->UpdateSubPrimaryComponents();
		}
	}

	void ScenePrimaryComponent::DebugUpdateSubPrimaryComponents()
	{
		DebugUpdate();
		for (auto&& component : subPrimaryComponent)
		{
			component->DebugUpdateSubPrimaryComponents();
		}
	}
}
