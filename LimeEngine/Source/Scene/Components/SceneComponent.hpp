#pragma once
#include "Scene/ScenePrimaryComponent.hpp"
#include "Base/Transformable.hpp"

namespace LimeEngine
{
	class Engine;

	class SceneComponent : public ScenePrimaryComponent, public Transformable
	{
	public:
		explicit SceneComponent(Engine* engine, const std::string& componentName = "SceneComponent", const Transform& transform = {}) noexcept;
		SceneComponent(SceneComponent&&) noexcept = default;
		SceneComponent& operator=(SceneComponent&&) noexcept = default;
		virtual ~SceneComponent() noexcept = default;

		SceneComponent* SetupAttachment(std::unique_ptr<SceneComponent>&& component) noexcept;
		template <typename T, typename... TArgs>
		T* SetupAttachment(TArgs&&... args) noexcept
		{
			return reinterpret_cast<T*>(SetupAttachment(std::make_unique<T>(std::forward<TArgs>(args)...)));
		}
		const std::vector<std::unique_ptr<SceneComponent>>& GetSubComponents() const noexcept;

		const std::string& GetComponentName() const noexcept;
		TempTransformMatrix GetWorldTransformMatrix() const noexcept override;
		void SetRootTransform(Transformable* rootTransform) noexcept;

	protected:
		Transformable* rootTransform = nullptr;
		Engine* engine = nullptr;
	};
}
