#pragma once
#include "SceneObject.hpp"

namespace LimeEngine
{
	class SceneMap
	{
	protected:
		virtual void Update();
		virtual void Render();
	public:
		SceneMap(Engine* engine);
		virtual void Load();;
		void UpdateMap();
		void RenderMap();
		void AttachObject(std::unique_ptr<SceneObject>&& object);
		virtual ~SceneMap() noexcept = default;
	public:
		std::vector<std::unique_ptr<SceneObject>> objects;
	protected:
		Engine* engine = nullptr;
	};
}