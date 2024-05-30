// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Engine.hpp"
#include "Graphics/Renderer.hpp"

namespace LimeEngine
{
	Engine::Engine() : windowLayer(), inputLayer(), renderLayer(), dataLayer(), sceneLayer(), editorLayer() {}

	int Engine::Start()
	{
		LE_CORE_LOG_TRACE("Engine start");
		timer.Start();
		while (!exitCode.has_value())
		{
			deltaTime = timer.ElapsedTime();
			timer.Restart();
			UpdateLayers();
		}
		LE_CORE_LOG_TRACE("Engine close with code {}", *exitCode);
		return *exitCode;
	}

	void Engine::UpdateLayers()
	{
		RuntimeEditor::Processing(deltaTime);
		dataLayer.Update();
		windowLayer.Update();
		inputLayer.Update();
		sceneLayer.Update();
		editorLayer.Update();
		renderLayer.Update();
	}

	void Engine::Close(int exitCode)
	{
		this->exitCode = exitCode;
	}

	void Engine::Close(const Event& e)
	{
		Close(CastEvent<CloseWindowEvent>(e).exitCode);
	}

	// static

	void Engine::Initialize()
	{
		// TODO: Load settings from file
		WindowLayer::GetWindowLayer().SetWindow(WindowArgs(TEXT("LimeEngine"), 1080, 720));
	}

	Engine& Engine::GetEngine() noexcept
	{
		return engine;
	}
}
