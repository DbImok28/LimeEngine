// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Graphics/Renderer.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
#ifdef LE_ENABLE_CONSOLE
	URef<Console> Console::mainConsole = Console::Create({});
#endif

	Logger Logger::coreLogger{ "Engine" };
	Logger Logger::appLogger{ "App" };

	Renderer Renderer::renderer;
	Engine Engine::engine;
}
