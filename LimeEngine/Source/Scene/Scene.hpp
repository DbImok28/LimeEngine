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
		const std::vector<std::unique_ptr<SceneMap>>& GetSubMaps() const noexcept;

		std::string GetSceneName() const noexcept;

	private:
		Engine* engine = nullptr;
	};
}
