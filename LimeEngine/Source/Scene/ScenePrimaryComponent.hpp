// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once

namespace LimeEngine
{
	class SceneLayer;
	class Scene;

	enum class SceneComponentState
	{
		WaitForInit,
		WaitForBegin,
		Started,
		WaitForEnd,
		WaitForDestroy
	};

	class ScenePrimaryComponent
	{
		friend class SceneLayer;
		friend class Scene;

		LE_DELETE_COPY(ScenePrimaryComponent)

	public:
		ScenePrimaryComponent(const std::string& primaryName = "ScenePrimaryComponent") : primaryName(primaryName) {}
		ScenePrimaryComponent(ScenePrimaryComponent&&) noexcept = default;
		ScenePrimaryComponent& operator=(ScenePrimaryComponent&&) noexcept = default;

		virtual ~ScenePrimaryComponent() noexcept;

	protected:
		const std::vector<URef<ScenePrimaryComponent>>& GetSubPrimaryComponents() const noexcept;
		ScenePrimaryComponent* SetupPrimaryAttachment(URef<ScenePrimaryComponent>&& component) noexcept;

		URef<ScenePrimaryComponent> PrimaryDetach(ScenePrimaryComponent* component) noexcept;
		void PrimaryDetachDestroy(ScenePrimaryComponent* component) noexcept;
		URef<ScenePrimaryComponent> PrimaryDetach() noexcept;
		void PrimaryDetachDestroy() noexcept;

		virtual void Init()
		{
			LE_CORE_LOG_DEBUG("Init: {}", GetPathInSceneHierarchy());
		}
		virtual void Begin()
		{
			LE_CORE_LOG_DEBUG("Begin: {}", GetPathInSceneHierarchy());
		}
		virtual void End()
		{
			LE_CORE_LOG_DEBUG("End: {}", GetPathInSceneHierarchy());
		}

		virtual void Update() {}
		virtual void DebugUpdate() {}

	private:
		void PropagateUpdate();
		void PropagateDebugUpdate();
		void PropagateInit();
		void PropagateBegin();
		void PropagateEnd();

	public:
		void Destroy();
		void DestroyImmediately();

		Scene* GetScene() const noexcept;

		const std::string& GetPrimaryName() const noexcept;
		std::string GetPathInSceneHierarchy() const noexcept
		{
			return primaryOwner ? std::format("{}/{}", primaryOwner->GetPathInSceneHierarchy(), GetPrimaryName()) : GetPrimaryName();
		}

	private:
		std::string primaryName;
		size_t primaryUniqueId;
		ScenePrimaryComponent* primaryOwner = nullptr;
		std::vector<URef<ScenePrimaryComponent>> subPrimaryComponent;
		SceneComponentState primaryComponentState = SceneComponentState::WaitForInit;
	};

	// Automatically continue component initialization in destructor
	//	template <std::derived_from<ScenePrimaryComponent> TComponent>
	//	class SpawnHandler
	//	{
	//		friend Scene;
	//
	//	private:
	//		SpawnedSceneComponent(TComponent* component) noexcept : component(component) {}
	//
	//	public:
	//		~SpawnedSceneComponent() noexcept
	//		{
	//			if (component) component->Init();
	//		}
	//
	//		TComponent& operator*() const
	//		{
	//			LE_ASSERT(component);
	//			return component;
	//		}
	//
	//		TComponent* operator->() const
	//		{
	//			LE_ASSERT(component);
	//			return component;
	//		}
	//
	//		operator bool() const
	//		{
	//			return component;
	//		}
	//
	//		bool IsValid() const
	//		{
	//			return component;
	//		}
	//
	//		TComponent* Get() const
	//		{
	//			return component;
	//		}
	//
	//		void ContinueSpawning() const
	//		{
	//			if (component)
	//			{
	//				component->Init();
	//				component = nullptr;
	//			}
	//		}
	//
	//	private:
	//		TComponent* component;
	//	};
}
