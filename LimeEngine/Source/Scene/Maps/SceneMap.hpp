#pragma once
#include "Scene/Objects/SceneObject.hpp"

namespace LimeEngine
{
	class SceneMap : public ScenePrimaryComponent
	{

	public:
		explicit SceneMap(Engine* engine, const std::string& mapName = "SceneMap");
		virtual ~SceneMap() noexcept = default;

		virtual void Load(){};

		SceneObject* SetupAttachment(std::unique_ptr<SceneObject>&& object);
		const std::vector<std::unique_ptr<SceneObject>>& GetSubObjects() const noexcept;

		std::string GetMapName() const noexcept;

	protected:
		Engine* engine = nullptr;
	};
}
