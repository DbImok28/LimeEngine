// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Engine.hpp"
#include "Graphics/Renderer.hpp"

namespace LimeEngine
{
	LE_DEFINE_LOGGER(LogEngine);

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
		LE_LOG_TRACE(LogEngine, "Engine Init");
		// dataLayer.Init();
		// windowLayer.Init();
		// inputLayer.Init();
		// sceneLayer.Init();
		// editorLayer.Init();
		// renderLayer.Init();
		layerManager.Init();

		timer.Start();

		LE_LOG_TRACE(LogEngine, "Engine Begin");
		// dataLayer.Begin();
		// windowLayer.Begin();
		// inputLayer.Begin();
		// sceneLayer.Begin();
		// editorLayer.Begin();
		// renderLayer.Begin();
		layerManager.Begin();

		LE_LOG_TRACE(LogEngine, "Engine start Update Loop");
		while (!exitCode.has_value())
		{
			deltaTime = timer.ElapsedTime();
			timer.Restart();
			UpdateLayers();
		}

		LE_LOG_TRACE(LogEngine, "Engine End");
		//		sceneLayer.End();
		//		editorLayer.End();
		//		renderLayer.End();
		//		inputLayer.End();
		//		windowLayer.End();
		//		dataLayer.End();
		layerManager.End();

		LE_LOG_TRACE(LogEngine, "Engine close with code {}", *exitCode);
		return *exitCode;
	}

	void Engine::UpdateLayers()
	{
		RuntimeEditor::Processing(deltaTime);

		if (RuntimeEditor::BeginPanel("Engine"))
		{
			if (RuntimeEditor::Button("Close")) exitCode = 0;

			static std::string loggerName = "LogEngine";
			static std::string logMessage = "Hello";
			LogLevel logLevel = LogLevel::Debug;

			RuntimeEditor::TextField("LoggerName", loggerName);
			RuntimeEditor::TextField("Message", logMessage);
			//RuntimeEditor::Combobox("Level", logLevel);

			std::optional<Logger> loggerOpt = LoggerManager::TryGetLogger(loggerName);
			if (loggerOpt)
			{
				Logger logger = *loggerOpt;
				if (RuntimeEditor::Button("Trace")) logger.Log(LogLevel::Trace, logMessage);
				if (RuntimeEditor::Button("Debug")) logger.Log(LogLevel::Debug, logMessage);
				if (RuntimeEditor::Button("Info")) logger.Log(LogLevel::Info, logMessage);
				if (RuntimeEditor::Button("Warning")) logger.Log(LogLevel::Warning, logMessage);
				if (RuntimeEditor::Button("Error")) logger.Log(LogLevel::Error, logMessage);
				if (RuntimeEditor::Button("CriticalError")) logger.Log(LogLevel::CriticalError, logMessage);
			}

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
