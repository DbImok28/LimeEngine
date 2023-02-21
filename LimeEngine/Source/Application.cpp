#include "lepch.hpp"
#include "Application.hpp"
#include "CoreBase.hpp"
#include "Engine.hpp"

#include "Scene/TestMap.hpp"

#ifdef LE_ENABLE_COM
	#include <objbase.h>
#endif

namespace LimeEngine
{
	void Application::Run()
	{
#ifdef LE_ENABLE_COM
		CHECK_HR(CoInitializeEx(NULL, COINIT_MULTITHREADED));
#endif
		Logger::StaticInitialize();

		// Renderer
		auto window = Window::Create({ TEXT("LimeEngine"), 1080, 720 });
		auto renderer = Renderer::Create(RenderAPI::Auto, *window.get());

		// Create Engine
		Engine engine(std::move(window), std::move(renderer));

		// Load map
		Logger::GetCoreLogger().Log(LogLevel::Info, "Load map");
		auto map = std::make_unique<TestMap>(&engine);
		map->Load();
		engine.sceneLayer.GetScene().AttachMap(std::move(map));

		// Start Engine
		Logger::GetCoreLogger().Log(LogLevel::Info, "Engine startup");
		engine.Start();
	}
}
