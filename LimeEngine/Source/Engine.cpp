// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Engine.hpp"
#include "Graphics/Renderer.hpp"

namespace LimeEngine
{
	Engine::Engine() : windowLayer(), inputLayer(), renderLayer(), dataLayer(), sceneLayer(), editorLayer()
	{
		inputLayer = layerManager.EmplaceLayer<InputLayer>();
		windowLayer = layerManager.EmplaceLayer<WindowLayer>();
		dataLayer = layerManager.EmplaceLayer<DataLayer>();
		renderLayer = layerManager.EmplaceLayer<RenderLayer>();
		sceneLayer = layerManager.EmplaceLayer<SceneLayer>();
		editorLayer = layerManager.EmplaceLayer<EditorLayer>();
	}

	int Engine::Start()
	{
		// TODO: Add engine layers storage class (Add Layer priority and dependency)
		LE_CORE_LOG_TRACE("Engine Init");
		// dataLayer.Init();
		// windowLayer.Init();
		// inputLayer.Init();
		// sceneLayer.Init();
		// editorLayer.Init();
		// renderLayer.Init();
		layerManager.Init();

		timer.Start();

		LE_CORE_LOG_TRACE("Engine Begin");
		// dataLayer.Begin();
		// windowLayer.Begin();
		// inputLayer.Begin();
		// sceneLayer.Begin();
		// editorLayer.Begin();
		// renderLayer.Begin();
		layerManager.Begin();

		LE_CORE_LOG_TRACE("Engine start Update Loop");
		while (!exitCode.has_value())
		{
			deltaTime = timer.ElapsedTime();
			timer.Restart();
			UpdateLayers();
		}

		LE_CORE_LOG_TRACE("Engine End");
		//		sceneLayer.End();
		//		editorLayer.End();
		//		renderLayer.End();
		//		inputLayer.End();
		//		windowLayer.End();
		//		dataLayer.End();
		layerManager.End();

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

		layerManager.PreUpdate();
#if defined(LE_DEBUG)
		//		dataLayer.DebugUpdate();
		//		windowLayer.DebugUpdate();
		//		inputLayer.DebugUpdate();
		//		sceneLayer.DebugUpdate();
		//		editorLayer.DebugUpdate();
		//		renderLayer.DebugUpdate();
		layerManager.DebugUpdate();
#endif
		//		dataLayer.Update();
		//		windowLayer.Update();
		//		inputLayer.Update();
		//		sceneLayer.Update();
		//		editorLayer.Update();
		//		renderLayer.Update();
		layerManager.Update();
		layerManager.PostUpdate();
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
		WindowLayer::GetWindowLayer()->AddWindow(WindowArgs("MainWindow", TEXT("LimeEngine"), 1080, 720));

		Window* window = WindowLayer::GetWindowLayer()->GetWindow(0);
		Renderer::GetRenderer().CreateRenderOutput(RenderOutputArgs(window));
	}

	Engine* Engine::GetEngine() noexcept
	{
		return &engine;
	}
}
