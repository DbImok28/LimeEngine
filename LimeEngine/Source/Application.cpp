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
		Engine::Initialize();

		auto map = std::make_unique<TestMap>();
		map->Load();
		SceneLayer::GetSceneLayer().GetScene().SetupAttachment(std::move(map));
		Engine::GetEngine().Start();
	}
}
