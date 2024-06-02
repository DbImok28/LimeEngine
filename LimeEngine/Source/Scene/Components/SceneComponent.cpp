// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "SceneComponent.hpp"
#include "Scene/Objects/SceneObject.hpp"

namespace LimeEngine
{
	SceneComponent* SceneComponent::SetupAttachment(URef<SceneComponent>&& component) noexcept
	{
		auto attachedComponent = reinterpret_cast<SceneComponent*>(SetupPrimaryAttachment(std::move(component)));
		attachedComponent->SetRootTransform(this);
		return attachedComponent;
	}

	const std::vector<URef<SceneComponent>>& SceneComponent::GetSubComponents() const noexcept
	{
		return reinterpret_cast<const std::vector<URef<SceneComponent>>&>(GetSubPrimaryComponents());
	}

	const std::string& SceneComponent::GetComponentName() const noexcept
	{
		return GetPrimaryName();
	}

	void SceneComponent::SetRootTransform(Transformable* rootTransform) noexcept
	{
		this->rootTransform = rootTransform;
	}

	TempTransformMatrix SceneComponent::GetWorldTransformMatrix() const noexcept
	{
		if (rootTransform)
		{
			return GetTransform().GetTransformMatrix() * rootTransform->GetWorldTransformMatrix();
		}
		else
		{
			return GetTransform().GetTransformMatrix();
		}
	}
}
