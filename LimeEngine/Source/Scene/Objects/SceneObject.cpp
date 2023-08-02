// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "SceneObject.hpp"

namespace LimeEngine
{
	SceneObject::SceneObject(Engine* engine, const std::string& objectName) noexcept : SceneComponent(engine, objectName) {}

	std::string SceneObject::GetObjectName() const noexcept
	{
		return GetComponentName();
	}

	Transform SceneObject::GetObjectTransform() const noexcept
	{
		return GetTransform();
	}
}
