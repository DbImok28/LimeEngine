// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Application.hpp"
#include "CoreBase.hpp"
#include "Engine.hpp"
#include "Base/StaticInitializer.hpp"
#include "Platform/Platform.hpp"

#include "Scene/Maps/TestMap.hpp"

namespace LimeEngine
{
	Application::Application()
	{
		Platform::Initialize();
		Initialize();
		StaticInitializer::Initialize();
	}

	void Application::Initialize() {}

	void Application::Run()
	{
		auto window = Window::Create(WindowArgs(TEXT("LimeEngine"), 1080, 720));
		//auto renderer = Renderer::Create(*window.get(), DisplayMode::Windowed, false);
		/*Renderer::GetRenderer().Init(RenderOutputArgs(window.get()), RendererArgs{});*/
		Renderer::Create(RenderOutputArgs(window.get()), RendererArgs{});

		Engine engine(std::move(window));

		auto map = std::make_unique<TestMap>(&engine);
		map->Load();
		engine.sceneLayer.GetScene().SetupAttachment(std::move(map));

		engine.Start();
	}
}
