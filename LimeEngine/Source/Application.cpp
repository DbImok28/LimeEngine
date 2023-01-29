#include "lepch.hpp"
#include "Application.hpp"
#include "CoreBase.hpp"
#include "Engine.hpp"
#include "Graphics/Systems/DX11/RendererDX11.hpp"
#include "Scene/TestMap.hpp"

namespace LimeEngine
{
	void Application::Run()
	{
		CHECK_HR(CoInitialize(NULL));

		Logger::StaticInitialize();

		// Renderer
		auto outWindow = Window::Create({ TEXT("LimeEngine"), 1080, 720 });
		auto renderer = RendererDX11(outWindow.get());

		// Create Engine
		Engine engine(EngineIO(RenderIO(&renderer), SceneIO{}));

		// load map
		Logger::GetCoreLogger().Log(LogLevel::Info, "Load map");
		auto map = std::make_unique<TestMap>(&engine);
		map->Load();
		engine.scene.AttachMap(std::move(map));

		// Start Engine
		Logger::GetCoreLogger().Log(LogLevel::Info, "Engine startup");
		engine.Start();
	}
}
