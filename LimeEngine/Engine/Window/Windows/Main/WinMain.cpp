// Copyright (C) 2022 Pavel Jakushik - All Rights Reserved
// See file LICENSE for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "CoreBase.hpp"
#include "Engine.hpp"
#include "Graphics/Systems/DX11/RendererDX11.hpp"
#include "Scene/TestMap.hpp"
#include "Window/Windows/Console/Console.hpp"
#include <iostream>

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
	using namespace LimeEngine;
	try
	{
		CHECK_HR(CoInitialize(NULL));

		// Log
		auto logConsole = ConsoleWindows();

		// Renderer
		auto outWindow = Window(1080, 720, TEXT("LimeEngine"));
		auto renderer = RendererDX11(&outWindow);

		// Create Engine
		Engine engine(EngineIO(RenderIO(&renderer), SceneIO{}), &logConsole);

		// load map
		auto map = std::make_unique<TestMap>(&engine);
		map->Load();
		engine.scene.AttachMap(std::move(map));

		// Start Engine
		engine.Start();
		return EXIT_SUCCESS;
	}
	catch (const EngineException& e)
	{
		MessageBoxA(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONERROR);
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Standard exception", MB_OK | MB_ICONERROR);
	}
	catch (...)
	{
		MessageBoxA(nullptr, "No info", "Unknown exception", MB_OK | MB_ICONERROR);
	}
	return EXIT_FAILURE;
}