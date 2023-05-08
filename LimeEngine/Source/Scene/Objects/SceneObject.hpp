#pragma once
#include "Scene/Components/SceneComponent.hpp"

namespace LimeEngine
{
	class SceneObject : public SceneComponent
	{
	public:
		SceneObject(Engine* engine, const std::string& objectName = "SceneObject", const Transform& transform = {}) noexcept;
		virtual ~SceneObject() noexcept = default;

		std::string GetObjectName() const noexcept;
		Transform GetObjectTransform() const noexcept;

	protected:
		Engine* engine = nullptr;
	};
}
