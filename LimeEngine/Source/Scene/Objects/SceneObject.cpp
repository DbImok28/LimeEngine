#include "lepch.hpp"
#include "SceneObject.hpp"

namespace LimeEngine
{
	SceneObject::SceneObject(Engine* engine, const std::string& objectName, const Transform& transform) noexcept : engine(engine), SceneComponent(engine, objectName, transform) {}

	std::string SceneObject::GetObjectName() const noexcept
	{
		return GetComponentName();
	}

	Transform SceneObject::GetObjectTransform() const noexcept
	{
		return GetTransform();
	}
}
