#pragma once
#include "EngineLayer.hpp"
#include "Base/GameDataManager.hpp"

namespace LimeEngine
{
	class DataLayer : public EngineLayer
	{
		LE_DELETE_COPY(DataLayer)

	public:
		DataLayer(Engine* engine, const GraphicFactory* graphicFactory);

		void Update() override;
		GameDataManager& GetGameDataManager() noexcept;

	private:
		GameDataManager gameDataManager;
	};
}