#pragma once

namespace LimeEngine
{
	class SceneLayer;

	class ScenePrimaryComponent
	{
		friend SceneLayer;

	public:
		ScenePrimaryComponent(const std::string& primaryName = "ScenePrimaryComponent") : primaryName(primaryName) {}
		ScenePrimaryComponent(ScenePrimaryComponent&&) noexcept = default;
		ScenePrimaryComponent& operator=(ScenePrimaryComponent&&) noexcept = default;

		virtual ~ScenePrimaryComponent() = default;

		const std::string& GetPrimaryName() const noexcept
		{
			return primaryName;
		}

	protected:
		const std::vector<std::unique_ptr<ScenePrimaryComponent>>& GetSubPrimaryComponents() const noexcept
		{
			return subPrimaryComponent;
		}

		ScenePrimaryComponent* SetupPrimaryAttachment(std::unique_ptr<ScenePrimaryComponent>&& component) noexcept
		{
			subPrimaryComponent.push_back(std::move(component));
			return subPrimaryComponent.back().get();
		}

		virtual void Update(){};
		virtual void DebugUpdate(){};

	private:
		void UpdateSubPrimaryComponents()
		{
			Update();
			for (auto&& component : subPrimaryComponent)
			{
				component->UpdateSubPrimaryComponents();
			}
		}
		void DebugUpdateSubPrimaryComponents()
		{
			DebugUpdate();
			for (auto&& component : subPrimaryComponent)
			{
				component->DebugUpdateSubPrimaryComponents();
			}
		}

	private:
		std::string primaryName;
		std::vector<std::unique_ptr<ScenePrimaryComponent>> subPrimaryComponent;
	};
}
