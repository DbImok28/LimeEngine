#pragma once
/*
* Copyright(C) 2021, by ѕавел якушик(ruby.circles774@gmail.com)
*/
#include "Window/Window.hpp"
#include "Helpers/Timer.hpp"
#include "Scene/Scene.hpp"
#include "Base/GameDataManager.hpp"

class Engine
{
public:
	Engine(const Engine&) = delete;
	Engine(Engine&&) noexcept = delete;
	Engine& operator=(const Engine&) = delete;
	Engine& operator=(Engine&&) noexcept = delete;
	Engine(const wchar_t* windowTitle = L"GameEngine", int width = 1080, int height = 720);

	void Initialize();
	int Start();
	void Processing();
	void RenderFrame();
public:
	float deltaTime = 0;
	Window window;
	Scene scene;
	GameDataManager gameDataManager;
	Timer timer;
};