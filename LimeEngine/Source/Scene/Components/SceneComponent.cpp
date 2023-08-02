// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "SceneComponent.hpp"
#include "SceneComponent.hpp"
#include "lepch.hpp"
#include "SceneComponent.hpp"
#include "Scene/Objects/SceneObject.hpp"

namespace LimeEngine
{
	SceneComponent::SceneComponent(Engine* engine, const std::string& componentName) noexcept : engine(engine), ScenePrimaryComponent(componentName), Transformable() {}

	SceneComponent* SceneComponent::SetupAttachment(std::unique_ptr<SceneComponent>&& component) noexcept
	{
		auto attachedComponent = reinterpret_cast<SceneComponent*>(SetupPrimaryAttachment(std::move(component)));
		attachedComponent->SetRootTransform(this);
		return attachedComponent;
	}

	const std::vector<std::unique_ptr<SceneComponent>>& SceneComponent::GetSubComponents() const noexcept
	{
		return reinterpret_cast<const std::vector<std::unique_ptr<SceneComponent>>&>(GetSubPrimaryComponents());
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
