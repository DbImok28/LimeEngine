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
		// TODO: Add engine layers storage class (Add Layer priority and dependency)
		LE_CORE_LOG_TRACE("Engine Init");
		dataLayer.Init();
		windowLayer.Init();
		inputLayer.Init();
		sceneLayer.Init();
		editorLayer.Init();
		renderLayer.Init();

		timer.Start();

		LE_CORE_LOG_TRACE("Engine Begin");
		dataLayer.Begin();
		windowLayer.Begin();
		inputLayer.Begin();
		sceneLayer.Begin();
		editorLayer.Begin();
		renderLayer.Begin();

		LE_CORE_LOG_TRACE("Engine start Update Loop");
		while (!exitCode.has_value())
		{
			deltaTime = timer.ElapsedTime();
			timer.Restart();
			UpdateLayers();
		}

		LE_CORE_LOG_TRACE("Engine End");
		sceneLayer.End();
		editorLayer.End();
		renderLayer.End();
		inputLayer.End();
		windowLayer.End();
		dataLayer.End();

		LE_CORE_LOG_TRACE("Engine close with code {}", *exitCode);
		return *exitCode;
	}

	void Engine::UpdateLayers()
	{
		RuntimeEditor::Processing(deltaTime);

		if (RuntimeEditor::BeginPanel("Engine"))
		{
			if (RuntimeEditor::Button("Close")) exitCode = 0;
			RuntimeEditor::EndPanel();
		}

#if defined(LE_DEBUG)
		dataLayer.DebugUpdate();
		windowLayer.DebugUpdate();
		inputLayer.DebugUpdate();
		sceneLayer.DebugUpdate();
		editorLayer.DebugUpdate();
		renderLayer.DebugUpdate();
#endif

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
