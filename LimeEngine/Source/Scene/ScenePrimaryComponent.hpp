// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once

namespace LimeEngine
{
	class SceneLayer;

	class ScenePrimaryComponent
	{
		friend SceneLayer;
		LE_DELETE_COPY(ScenePrimaryComponent)

	public:
		ScenePrimaryComponent(const std::string& primaryName = "ScenePrimaryComponent") : primaryName(primaryName) {}
		ScenePrimaryComponent(ScenePrimaryComponent&&) noexcept = default;
		ScenePrimaryComponent& operator=(ScenePrimaryComponent&&) noexcept = default;

		virtual ~ScenePrimaryComponent() = default;

		const std::string& GetPrimaryName() const noexcept;

	protected:
		const std::vector<URef<ScenePrimaryComponent>>& GetSubPrimaryComponents() const noexcept;
		ScenePrimaryComponent* SetupPrimaryAttachment(URef<ScenePrimaryComponent>&& component) noexcept;

		virtual void Update() {};
		virtual void DebugUpdate() {};

	private:
		void UpdateSubPrimaryComponents();
		void DebugUpdateSubPrimaryComponents();

	private:
		std::string primaryName;
		std::vector<URef<ScenePrimaryComponent>> subPrimaryComponent;
	};
}
