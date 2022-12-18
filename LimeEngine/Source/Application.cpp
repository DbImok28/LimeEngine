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

		Logger::Initialize();

		// Renderer
		auto outWindow = Window(1080, 720, TEXT("LimeEngine"));
		auto renderer = RendererDX11(&outWindow);

		// Create Engine
		Engine engine(EngineIO(RenderIO(&renderer), SceneIO{}));

		// load map
		Logger::GetCoreLogger().Log(LogLevel::Info, "Load map");
		auto map = std::make_unique<TestMap>(&engine);
		map->Load();
		engine.scene.AttachMap(std::move(map));

		// Start Engine
		Logger::GetCoreLogger().Log(LogLevel::Info, "Engine startup");

		LE_CORE_TRACE("Hi Core {0}", 1);
		LE_CORE_INFO("Hi Core {0}", 1);
		LE_CORE_DEBUG("Hi Core {0}", 1);
		LE_CORE_WARNING("Hi Core {0}", 1);
		LE_CORE_ERROR("Hi Core {0}", 1);
		LE_CORE_CRITICAL_ERROR("Hi Core {0}", 1);
		LE_TRACE("Hi User");
		LE_INFO("Hi User {0}", 1);
		LE_DEBUG("Hi User {0}", 1);
		LE_WARNING("Hi User {0}", 1);
		LE_ERROR("Hi User {0}", 1);
		LE_CRITICAL_ERROR("Hi User {0}", 1);

		engine.Start();
	}
}
