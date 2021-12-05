#include "SceneComponent.hpp"
#include "SceneObject.hpp"

namespace LimeEngine
{
	void SceneComponent::Initialize(Engine* engine, SceneObject* rootObject)
	{
		this->engine = engine;
		this->rootObject = rootObject;
	}

	void SceneComponent::Update()
	{

	}

	void SceneComponent::Render()
	{

	}

	TempTransformMatrix SceneComponent::GetWorldTransformMatrix() const noexcept
	{
		//return (GetTransform() * rootObject->GetTransform()).GetTransformMatrix();
		return GetTransform().GetTransformMatrix() * rootObject->GetTransform().GetTransformMatrix();
	}
}