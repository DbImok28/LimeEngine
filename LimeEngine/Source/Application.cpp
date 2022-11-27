#include "Application.hpp"
#include "CoreBase.hpp"
#include "Engine.hpp"
#include "Graphics/Systems/DX11/RendererDX11.hpp"
#include "Scene/TestMap.hpp"
#include "Window/Windows/Console/Console.hpp"

namespace LimeEngine
{
	void Application::Run()
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
	}
}
