// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Application.hpp"
#include "CoreBase.hpp"
#include "Engine.hpp"
#include "Base/StaticInitializer.hpp"
#include "Platform/Platform.hpp"
#include "Graphics/RenderAPI.hpp"
#include "Window/Console.hpp"

#include "Scene/Maps/TestMap.hpp"

namespace LimeEngine
{
	Application::Application()
	{
		if (autoRunConsole)
		{
			// TODO: Read console args from config
			ConsoleArgs consoleArgs;
			consoleArgs.title = "OutConsole";
			console = Console::Create(consoleArgs);
			loggerConsole = MakeUnique<LoggerConsole>(console.get());
		}

		Platform::Initialize();
		Initialize();
		StaticInitializer::Initialize();
		RenderAPI::Initialize();
		Engine::Initialize();
	}

	void Application::Initialize() {}

	void Application::Run()
	{
		auto map = MakeUnique<TestMap>();
		map->Load();
		SceneLayer::GetSceneLayer()->GetScene()->SetupAttachment(std::move(map));
		Engine::GetEngine()->Start();
	}

	Console* Application::GetConsole() const
	{
		return console.get();
	}
}
