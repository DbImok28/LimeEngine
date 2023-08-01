// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "lepch.hpp"
#include "WindowLayer.hpp"

namespace LimeEngine
{
	WindowLayer::WindowLayer(Engine* engine, std::unique_ptr<Window>&& window) : EngineLayer(engine), window(std::move(window)) {}

	void WindowLayer::Update()
	{
		window->OnUpdate();
	}

	Window& WindowLayer::GetWindow() noexcept
	{
		return *window.get();
	}
}