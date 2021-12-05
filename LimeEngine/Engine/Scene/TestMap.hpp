#pragma once
#include "SceneMap.hpp"

namespace LimeEngine
{
	class TestMap : public SceneMap
	{
	public:
		void Initialize(Engine* engine) override;
	};
}