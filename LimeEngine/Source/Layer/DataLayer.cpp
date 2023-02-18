#pragma once
#include "lepch.hpp"
#include "DataLayer.hpp"

namespace LimeEngine
{
	DataLayer::DataLayer(Engine* engine, const GraphicFactory* graphicFactory) : EngineLayer(engine), gameDataManager(engine, graphicFactory) {}

	void DataLayer::Update()
	{
		gameDataManager.Update();
	}

	GameDataManager& DataLayer::GetGameDataManager() noexcept
	{
		return gameDataManager;
	}
}