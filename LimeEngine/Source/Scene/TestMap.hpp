#pragma once
#include "SceneMap.hpp"

namespace LimeEngine
{
	class TestMap : public SceneMap
	{
	public:
		using SceneMap::SceneMap;
		void Load() override;
		void Update() override;
	};
}