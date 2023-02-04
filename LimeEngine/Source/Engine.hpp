// Developed by Pavel Jakushik.
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#pragma once
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
	public:
		Engine(std::unique_ptr<Window>&& window, std::unique_ptr<Renderer>&& renderer);
		Engine(const Engine&) = delete;
		Engine(Engine&&) noexcept = delete;
		Engine& operator=(const Engine&) = delete;
		Engine& operator=(Engine&&) noexcept = delete;

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