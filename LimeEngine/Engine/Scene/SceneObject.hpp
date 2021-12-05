#pragma once
#include "SceneComponent.hpp"

namespace LimeEngine
{
	class SceneObject : public Transformable
	{
	public:
		virtual ~SceneObject() noexcept = default;
		virtual void Initialize(Engine* engine);
		virtual void Update();
		virtual void Render();

		void InitializeComponents();
		void UpdateComponents();
		void RenderComponents();
		void AttachComponent(std::unique_ptr<SceneComponent>&& component) noexcept;

		TempTransformMatrix GetWorldTransformMatrix() const noexcept override;
	public:
		std::vector<std::unique_ptr<SceneComponent>> components;
	protected:
		Engine* engine = nullptr;
	};
}