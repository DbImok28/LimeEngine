// Developed by Pavel Jakushik.
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#pragma once
#include <vector>
#include "IO/EngineIO.hpp"
#include "Helpers/Timer.hpp"
#include "Scene/Scene.hpp"
#include "Base/GameDataManager.hpp"

namespace LimeEngine
{
	class Engine
	{
	public:
		Engine(const Engine&) = delete;
		Engine(Engine&&) noexcept = delete;
		Engine& operator=(const Engine&) = delete;
		Engine& operator=(Engine&&) noexcept = delete;
		Engine();
		Engine(EngineIO&& engineIO);
		Engine(std::vector<EngineIO>&& engineIO);

		int Start();
		std::optional<int> EngineProcessing();
		std::optional<int> WindowProcessing();
		void RenderProcessing();

		void AddToRender(MeshComponent* meshComponent) noexcept;
		bool RemoveFromRender(const MeshComponent* meshComponent) noexcept;

	public:
		std::vector<EngineIO> engineIO;
		GameDataManager gameDataManager;
		Scene scene;
		Timer timer;
		float deltaTime = 0.0f;
	};
}