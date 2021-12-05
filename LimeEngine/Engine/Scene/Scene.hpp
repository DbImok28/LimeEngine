#pragma once
#include "SceneMap.hpp"

namespace LimeEngine
{
	class Scene
	{
	public:
		void Initialize(Engine* engine);
		void Update();
		void Render();

		void InitializeMaps();
		void UpdateMaps();
		void RenderMaps();
		void AttachMap(std::unique_ptr<SceneMap>&& map);

	public:
		std::vector<std::unique_ptr<SceneMap>> maps;

	protected:
		Engine* engine = nullptr;
	};
}