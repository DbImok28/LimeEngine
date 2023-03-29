#include "lepch.hpp"
#include "Application.hpp"
#include "CoreBase.hpp"
#include "Engine.hpp"
#include "Base/StaticInitializer.hpp"

#include "Scene/Maps/TestMap.hpp"

#ifdef LE_ENABLE_COM
	#include "Platform/Windows/WindowsExceptions.hpp"
	#include <objbase.h>
#endif

namespace LimeEngine
{
	void Application::Run()
	{
#ifdef LE_ENABLE_COM
		CHECK_HR(CoInitializeEx(NULL, COINIT_MULTITHREADED));
#endif
		StaticInitializer::Initialize();
		auto window = Window::Create(WindowArgs(TEXT("LimeEngine"), 1080, 720));
		auto renderer = Renderer::Create(RenderAPI::Auto, *window.get(), DisplayMode::Windowed, false);

		Engine engine(std::move(window), std::move(renderer));

		LE_CORE_LOG_TRACE("Load map");
		auto map = std::make_unique<TestMap>(&engine);
		map->Load();
		engine.sceneLayer.GetScene().AttachMap(std::move(map));

		engine.Start();
	}
}
