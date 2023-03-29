#include "lepch.hpp"
#include "SceneComponent.hpp"
#include "Scene/Objects/SceneObject.hpp"

namespace LimeEngine
{
	SceneComponent::SceneComponent(Engine* engine, const std::string& componentName, const Transform& transform) noexcept :
		engine(engine), componentName(componentName), Transformable(transform)
	{}

	void SceneComponent::Update() {}

	void SceneComponent::UpdateComponent()
	{
		Update();
		for (auto&& component : components)
		{
			component->UpdateComponent();
		}
	}

	void SceneComponent::AttachComponent(std::unique_ptr<SceneComponent>&& component) noexcept
	{
		components.push_back(std::move(component));
		components.back()->SetRootTransform(this);
	}

	const std::string& SceneComponent::GetComponentName() const noexcept
	{
		return componentName;
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