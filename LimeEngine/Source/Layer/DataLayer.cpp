// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "lepch.hpp"
#include "DataLayer.hpp"

namespace LimeEngine
{
	DataLayer::DataLayer(Engine* engine) : EngineLayer(engine), gameDataManager(engine) {}

	void DataLayer::Update()
	{
		gameDataManager.Update();
	}

	GameDataManager& DataLayer::GetGameDataManager() noexcept
	{
		return gameDataManager;
	}
}