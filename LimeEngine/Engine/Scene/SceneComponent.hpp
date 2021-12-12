#pragma once
#include <vector>
#include <memory>

#include "../Base/Transformable.hpp"

namespace LimeEngine
{
	class Engine;

	class SceneComponent : public Transformable
	{
	public:
		SceneComponent() noexcept = default;

		virtual void Initialize(Engine* engine, Transformable* rootTransform);
		virtual void Update();
		virtual void Render();
		void UpdateComponents();
		void RenderComponents();
		virtual ~SceneComponent() noexcept = default;

		void AttachComponent(std::unique_ptr<SceneComponent>&& component) noexcept;
		TempTransformMatrix GetWorldTransformMatrix() const noexcept override;

		std::vector<std::unique_ptr<SceneComponent>> components;
	protected:
		Transformable* rootTransform = nullptr;
		Engine* engine = nullptr;
	};
}