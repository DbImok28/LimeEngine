#include "SceneComponent.hpp"
#include "SceneObject.hpp"

namespace LimeEngine
{
	void SceneComponent::Initialize(Engine* engine, Transformable* rootTransform)
	{
		this->engine = engine;
		this->rootTransform = rootTransform;
	}

	void SceneComponent::Update()
	{
		UpdateComponents();
	}

	void SceneComponent::Render()
	{
		RenderComponents();
	}

	void SceneComponent::UpdateComponents()
	{
		for (auto&& component : components)
		{
			component->Update();
		}
	}

	void SceneComponent::RenderComponents()
	{
		for (auto&& component : components)
		{
			component->Render();
		}
	}

	void SceneComponent::AttachComponent(std::unique_ptr<SceneComponent>&& component) noexcept
	{
		components.push_back(std::move(component));
		components.back()->Initialize(engine, this);
	}

	TempTransformMatrix SceneComponent::GetWorldTransformMatrix() const noexcept
	{
		return GetTransform().GetTransformMatrix() * rootTransform->GetWorldTransformMatrix();
	}
}