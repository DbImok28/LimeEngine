#include "SceneObject.hpp"

namespace LimeEngine
{
	void SceneObject::Initialize(Engine* engine)
	{
		this->engine = engine;
		InitializeComponents();
	}

	void SceneObject::Update()
	{
		UpdateComponents();
	}

	void SceneObject::Render()
	{
		RenderComponents();
	}

	void SceneObject::InitializeComponents()
	{
		for (auto&& component : components)
		{
			component->Initialize(engine, this);
		}
	}

	void SceneObject::UpdateComponents()
	{
		for (auto&& component : components)
		{
			component->Update();
		}
	}

	void SceneObject::RenderComponents()
	{
		for (auto&& component : components)
		{
			component->Render();
		}
	}

	void SceneObject::AttachComponent(std::unique_ptr<SceneComponent>&& component) noexcept
	{
		components.push_back(std::move(component));
		components.back()->Initialize(engine, this);
	}

	TempTransformMatrix SceneObject::GetWorldTransformMatrix() const noexcept
	{
		return GetTransform().GetTransformMatrix();
	}
}