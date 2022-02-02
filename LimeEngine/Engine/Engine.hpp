// Developed by Pavel Jakushik. 
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#pragma once

#include "Window/Window.hpp"
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
		Engine(const wchar_t* windowTitle = L"GameEngine", int width = 1080, int height = 720);

		int Start();
		std::optional<int> Processing();
		void RenderFrame();
	public:
		float deltaTime = 0.0f;
		Window window;
		Scene scene;
		GameDataManager gameDataManager;
		Timer timer;
	};
}