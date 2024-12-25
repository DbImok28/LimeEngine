// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "EngineLayer.hpp"
#include "Base/GameDataManager.hpp"

namespace LimeEngine
{
	class DataLayer : public EngineLayer
	{
		LE_DELETE_COPY(DataLayer)

	public:
		DataLayer() noexcept : EngineLayer("DataLayer"), gameDataManager() {};
		static DataLayer& GetDataLayer();

		virtual void Update() override;
		virtual void DebugUpdate() override;
		
		GameDataManager& GetGameDataManager() noexcept;

	private:
		GameDataManager gameDataManager;
	};
}
