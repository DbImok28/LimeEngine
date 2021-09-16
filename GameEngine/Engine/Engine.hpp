#pragma once
/*
* Copyright(C) 2021, by ѕавел якушик(ruby.circles774@gmail.com)
*/
#include "Window/Window.hpp"
#include "Input/InputDevice.hpp"
#include "Base/GameData.hpp"
#include "Helpers/Timer.hpp"

class Engine
{
public:
	Engine(const Engine&) = delete;
	Engine(Engine&&) noexcept = delete;
	Engine& operator=(const Engine&) = delete;
	Engine& operator=(Engine&&) noexcept = delete;
	Engine(const wchar_t* windowTitle = L"GameEngine", int width = 1080, int height = 720);

	int Start();
	void Processing();
	void RenderFrame();
public:
	float deltaTime = 0;
	Window window;
	GameData gameData;
	Timer timer;
};