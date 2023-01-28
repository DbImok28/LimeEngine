#pragma once
#include "Base/Transformable.hpp"

namespace LimeEngine
{
	class Engine;

	class SceneComponent : public Transformable
	{
	protected:
		virtual void Update();

	public:
		explicit SceneComponent(Engine* engine, const Transform& transform = {}) noexcept;
		virtual ~SceneComponent() noexcept = default;
		void UpdateComponent();
		void SetRootTransform(Transformable* rootTransform) noexcept;
		void AttachComponent(std::unique_ptr<SceneComponent>&& component) noexcept;
		TempTransformMatrix GetWorldTransformMatrix() const noexcept override;

		std::vector<std::unique_ptr<SceneComponent>> components;

	protected:
		Transformable* rootTransform = nullptr;
		Engine* engine = nullptr;
	};
}