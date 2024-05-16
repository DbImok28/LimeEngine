// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "lepch.hpp"
#include "DataLayer.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	DataLayer& DataLayer::GetDataLayer()
	{
		return GetEngine().dataLayer;
	}

	void DataLayer::Update()
	{
		gameDataManager.Update();
	}

	GameDataManager& DataLayer::GetGameDataManager() noexcept
	{
		return gameDataManager;
	}
}
