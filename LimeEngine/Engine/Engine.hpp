// Developed by Pavel Jakushik.
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#pragma once
#include <vector>
#include "IO/EngineIO.hpp"
#include "Helpers/Timer.hpp"
#include "Scene/Scene.hpp"
#include "Base/GameDataManager.hpp"
#include "Diagnostics/Logger.hpp"

namespace LimeEngine
{
	class Engine
	{
	public:
		Engine(const Engine&) = delete;
		Engine(Engine&&) noexcept = delete;
		Engine& operator=(const Engine&) = delete;
		Engine& operator=(Engine&&) noexcept = delete;

		Engine(EngineIO&& engineIO, Console* logConsole);
		//Engine(std::vector<EngineIO>&& engineIO, Console* logConsole);

		int Start();
		std::optional<int> EngineProcessing();
		std::optional<int> WindowProcessing();
		void RenderProcessing();

		void AddToRender(IDrawable* drawable);
		void RemoveFromRender(const IDrawable* drawable) noexcept;

	public:
		Logger logger;
		GameDataManager gameDataManager;
		Scene scene;
		std::vector<EngineIO> engineIO;
		Timer timer;
		float deltaTime = 0.0f;
	};
}