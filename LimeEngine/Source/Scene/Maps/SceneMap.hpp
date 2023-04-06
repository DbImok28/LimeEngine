#pragma once
#include "Scene/Objects/SceneObject.hpp"

namespace LimeEngine
{
	class SceneMap
	{
	protected:
		virtual void Update();
		virtual void DebugUpdate();

	public:
		explicit SceneMap(Engine* engine);
		virtual ~SceneMap() noexcept = default;

		void UpdateMap();
		void DebugUpdateMap();

		virtual void Load();
		void AttachObject(std::unique_ptr<SceneObject>&& object);

	public:
		std::vector<std::unique_ptr<SceneObject>> objects;

	protected:
		Engine* engine = nullptr;
	};
}
