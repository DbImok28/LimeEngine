// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "lepch.hpp"
#include "WindowLayer.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	WindowLayer::~WindowLayer()
	{
		Renderer::GetRenderer().RemoveRenderOutput();
	}

	WindowLayer& WindowLayer::GetWindowLayer()
	{
		return GetEngine().windowLayer;
	}

	void WindowLayer::Update()
	{
		if (window) window->OnUpdate();
	}

	Window& WindowLayer::GetWindow() noexcept
	{
		return *window.get();
	}

	void WindowLayer::SetWindow(std::unique_ptr<Window>&& window) noexcept
	{
		this->window = std::move(window);
	}
}
