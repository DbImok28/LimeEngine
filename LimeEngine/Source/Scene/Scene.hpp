#pragma once
#include "Maps/SceneMap.hpp"
#include "Components/DefaultPlayerCameraComponent.hpp"

namespace LimeEngine
{
	class Scene : public ScenePrimaryComponent
	{
	public:
		explicit Scene(Engine* engine);

		SceneMap* SetupAttachment(std::unique_ptr<SceneMap>&& map);
		template <std::derived_from<SceneMap> TMap, typename... TArgs>
		TMap* SetupAttachment(TArgs&&... args) noexcept
		{
			return reinterpret_cast<TMap*>(SetupAttachment(std::make_unique<TMap>(std::forward<TArgs>(args)...)));
		}
		const std::vector<std::unique_ptr<SceneMap>>& GetSubMaps() const noexcept;

		std::string GetSceneName() const noexcept;

	private:
		Engine* engine = nullptr;
	};
}
