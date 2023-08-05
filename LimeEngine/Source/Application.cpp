// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Application.hpp"
#include "CoreBase.hpp"
#include "Engine.hpp"
#include "Base/StaticInitializer.hpp"

#include "Scene/Maps/TestMap.hpp"

#if defined(LE_BUILD_PLATFORM_WINDOWS)
	#if defined(LE_ENABLE_COM)
		#include "Platform/Windows/WindowsExceptions.hpp"
		#include <objbase.h>
	#endif
#endif

namespace LimeEngine
{
#if defined(LE_BUILD_PLATFORM_WINDOWS)
	void Application::Initialize()
	{
	#if defined(LE_ENABLE_COM)
		CHECK_HR(CoInitializeEx(NULL, COINIT_MULTITHREADED));
	#endif
	}
#else
	void Application::Initialize() {}
#endif

	Application::Application()
	{
		Initialize();
		StaticInitializer::Initialize();
	}

	void Application::Run()
	{
		auto window = Window::Create(WindowArgs(TEXT("LimeEngine"), 1080, 720));
		auto renderer = Renderer::Create(RenderAPI::Auto, *window.get(), DisplayMode::Windowed, false);

		Engine engine(std::move(window), std::move(renderer));

		auto map = std::make_unique<TestMap>(&engine);
		map->Load();
		engine.sceneLayer.GetScene().SetupAttachment(std::move(map));

		engine.Start();
	}
}
