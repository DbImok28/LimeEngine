#include "SceneObject.hpp"

namespace LimeEngine
{
	SceneObject::SceneObject(Engine* engine) noexcept : engine(engine) {}

	SceneObject::SceneObject(Engine* engine, const Transform& transform) noexcept : engine(engine), rootComponent(std::make_unique<SceneComponent>(engine, transform)) {}

	SceneObject::SceneObject(Engine* engine, std::unique_ptr<SceneComponent>&& rootComponent) noexcept : engine(engine), rootComponent(std::move(rootComponent)) {}

	void SceneObject::Update() {}

	void SceneObject::UpdateObject()
	{
		Update();
		if (rootComponent != nullptr)
		{
			rootComponent->UpdateComponent();
		}
	}

	void SceneObject::SetRootComponent(std::unique_ptr<SceneComponent>&& newRootComponent) noexcept
	{
		rootComponent = std::move(newRootComponent);
	}

	Transform SceneObject::GetObjectTransform() const noexcept
	{
		if (rootComponent != nullptr)
		{
			return rootComponent->GetTransform();
		}
		return Transform();
	}
}