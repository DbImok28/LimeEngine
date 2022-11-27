#pragma once
#include "SceneComponent.hpp"

namespace LimeEngine
{
	class SceneObject
	{
	protected:
		// This constructor leaves the object invalid, it just initializes the Engine field
		explicit SceneObject(Engine* engine) noexcept;
		virtual void Update();

	public:
		SceneObject(Engine* engine, const Transform& transform) noexcept;
		SceneObject(Engine* engine, std::unique_ptr<SceneComponent>&& rootComponent) noexcept;
		void SetRootComponent(std::unique_ptr<SceneComponent>&& newRootComponent) noexcept;
		Transform GetObjectTransform() const noexcept;
		void UpdateObject();
		virtual ~SceneObject() noexcept = default;

	public:
		std::unique_ptr<SceneComponent> rootComponent = nullptr;

	protected:
		Engine* engine = nullptr;
	};
}