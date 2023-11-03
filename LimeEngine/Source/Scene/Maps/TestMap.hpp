// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "SceneMap.hpp"

namespace LimeEngine
{
	class TestMap : public SceneMap
	{
		LE_DELETE_COPY(TestMap)

	public:
		explicit TestMap(Engine* engine) : SceneMap(engine, "TestMap") {}

		void Load() override;
		virtual void Update() override;
	};
}