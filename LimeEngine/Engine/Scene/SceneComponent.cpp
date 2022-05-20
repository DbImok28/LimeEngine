#include "SceneComponent.hpp"
#include "SceneObject.hpp"

namespace LimeEngine
{
	SceneComponent::SceneComponent(Engine* engine, Transform transform) noexcept : engine(engine), Transformable(transform) {}

	void SceneComponent::Update()
	{
	}

	void SceneComponent::UpdateComponent()
	{
		Update();
		for (auto&& component : components)
		{
			component->UpdateComponent();
		}
	}

	void SceneComponent::SetRootTransform(Transformable* rootTransform) noexcept
	{
		this->rootTransform = rootTransform;
	}

	void SceneComponent::AttachComponent(std::unique_ptr<SceneComponent>&& component) noexcept
	{
		components.push_back(std::move(component));
		components.back()->SetRootTransform(this);
	}

	TempTransformMatrix SceneComponent::GetWorldTransformMatrix() const noexcept
	{
		if (rootTransform != nullptr)
		{
			return GetTransform().GetTransformMatrix() * rootTransform->GetWorldTransformMatrix();
		}
		else
		{
			return GetTransform().GetTransformMatrix();
		}
	}
}