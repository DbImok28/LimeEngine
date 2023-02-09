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