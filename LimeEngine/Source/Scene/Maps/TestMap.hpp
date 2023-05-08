#pragma once
#include "SceneMap.hpp"

namespace LimeEngine
{
	class TestMap : public SceneMap
	{
	public:
		TestMap(Engine* engine) : SceneMap(engine, "TestMap") {}

		void Load() override;
		virtual void Update() override;
	};
}