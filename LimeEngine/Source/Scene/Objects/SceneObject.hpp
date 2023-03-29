#pragma once
#include "Scene/Components/SceneComponent.hpp"

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
		virtual ~SceneObject() noexcept = default;

		void UpdateObject();

		const std::string& GetObjectName() const noexcept;
		void SetRootComponent(std::unique_ptr<SceneComponent>&& newRootComponent) noexcept;
		Transform GetObjectTransform() const noexcept;

	public:
		std::unique_ptr<SceneComponent> rootComponent = nullptr;

	protected:
		Engine* engine = nullptr;
	};
}