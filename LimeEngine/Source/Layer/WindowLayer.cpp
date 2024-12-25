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
		window->events.Unbind(WindowEventType::Close, &Engine::GetEngine(), &Engine::Close);
		Renderer::GetRenderer().RemoveRenderOutput();
	}

	WindowLayer& WindowLayer::GetWindowLayer()
	{
		return GetEngine().windowLayer;
	}

	void WindowLayer::Update()
	{
		EngineLayer::Update();
		if (window) window->OnUpdate();
	}

	void WindowLayer::SetWindow(URef<Window>&& window)
	{
		this->window = std::move(window);
		this->window->GetInput().SetInputDevice(&InputLayer::GetInputLayer().GetInputDevice());
		this->window->events.Bind(WindowEventType::Close, &Engine::GetEngine(), &Engine::Close);

		Renderer::GetRenderer().SetRenderOutput(RenderOutput::CreateWindowRenderOutput(RenderOutputArgs(this->window.get())));
	}

	void WindowLayer::SetWindow(const WindowArgs& windowArgs)
	{
		SetWindow(Window::Create(windowArgs));
	}

	Window& WindowLayer::GetWindow() noexcept
	{
		return *window.get();
	}
}
