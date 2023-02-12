// Developed by Pavel Jakushik.
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Helpers/Timer.hpp"
#include "Base/GameDataManager.hpp"
#include "Layer/WindowLayer.hpp"
#include "Layer/InputLayer.hpp"
#include "Layer/RenderLayer.hpp"
#include "Layer/SceneLayer.hpp"

namespace LimeEngine
{
	class Engine
	{
		LE_DELETE_MOVE_COPY(Engine)

	public:
		Engine(std::unique_ptr<Window>&& window, std::unique_ptr<Renderer>&& renderer);

		int Start();
		void UpdateLayers();

		void Close(const Event& e);

	private:
		std::optional<int> exitCode;

	public:
		GameDataManager gameDataManager;
		WindowLayer windowLayer;
		InputLayer inputLayer;
		RenderLayer renderLayer;
		SceneLayer sceneLayer;
		Timer timer;
		float deltaTime = 0.0f;
	};
}