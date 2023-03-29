#include "lepch.hpp"
#include "SceneObject.hpp"

namespace LimeEngine
{
	SceneObject::SceneObject(Engine* engine) noexcept : engine(engine) {}

	SceneObject::SceneObject(Engine* engine, const Transform& transform) noexcept :
		engine(engine), rootComponent(std::make_unique<SceneComponent>(engine, "SceneComponent", transform))
	{}

	SceneObject::SceneObject(Engine* engine, std::unique_ptr<SceneComponent>&& rootComponent) noexcept : engine(engine), rootComponent(std::move(rootComponent)) {}

	void SceneObject::Update() {}

	void SceneObject::UpdateObject()
	{
		Update();
		if (rootComponent)
		{
			rootComponent->UpdateComponent();
		}
	}

	const std::string& SceneObject::GetObjectName() const noexcept
	{
		if (rootComponent)
		{
			return rootComponent->GetComponentName();
		}
		return "None";
	}

	void SceneObject::SetRootComponent(std::unique_ptr<SceneComponent>&& newRootComponent) noexcept
	{
		rootComponent = std::move(newRootComponent);
	}

	Transform SceneObject::GetObjectTransform() const noexcept
	{
		if (rootComponent)
		{
			return rootComponent->GetTransform();
		}
		return Transform();
	}
}