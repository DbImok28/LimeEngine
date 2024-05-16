// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Scene/ScenePrimaryComponent.hpp"
#include "Base/Transformable.hpp"

namespace LimeEngine
{
	class Engine;

	class SceneComponent : public ScenePrimaryComponent, public Transformable
	{
	public:
		explicit SceneComponent(const std::string& componentName = "SceneComponent") noexcept : ScenePrimaryComponent(componentName), Transformable() {}
		SceneComponent(SceneComponent&&) noexcept = default;
		SceneComponent& operator=(SceneComponent&&) noexcept = default;
		virtual ~SceneComponent() noexcept = default;

		SceneComponent* SetupAttachment(std::unique_ptr<SceneComponent>&& component) noexcept;

		template <std::derived_from<SceneComponent> TComponent, typename... TArgs>
		TComponent* SetupAttachment(TArgs&&... args) noexcept
		{
			return reinterpret_cast<TComponent*>(SetupAttachment(std::make_unique<TComponent>(std::forward<TArgs>(args)...)));
		}
		const std::vector<std::unique_ptr<SceneComponent>>& GetSubComponents() const noexcept;

		const std::string& GetComponentName() const noexcept;
		TempTransformMatrix GetWorldTransformMatrix() const noexcept override;
		void SetRootTransform(Transformable* rootTransform) noexcept;

	protected:
		Transformable* rootTransform = nullptr;
	};
}
