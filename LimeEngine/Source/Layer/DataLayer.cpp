// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "lepch.hpp"
#include "DataLayer.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	DataLayer* DataLayer::GetDataLayer()
	{
		return GetEngine()->dataLayer;
	}

	void DataLayer::Update()
	{
		EngineLayer::Update();
		gameDataManager.Update();
	}

	void DataLayer::DebugUpdate()
	{
		EngineLayer::DebugUpdate();
		if (RuntimeEditor::BeginPanel("Assets"))
		{
			RuntimeEditor::Text(std::format("Assets {}", gameDataManager.GetAllResources().size()));
			for (auto& [path, ref] : gameDataManager.GetAllResources())
			{
				RuntimeEditor::Text(std::format("{}, refs: {}", ref->GetPath().GetPath(), ref->GetRefCount()));
			}
			RuntimeEditor::EndPanel();
		}
	}

	GameDataManager& DataLayer::GetGameDataManager() noexcept
	{
		return gameDataManager;
	}
}
