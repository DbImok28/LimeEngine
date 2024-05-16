// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	Engine::Engine() : windowLayer(), inputLayer(), renderLayer(), dataLayer(), sceneLayer(), editorLayer() {}

	Engine::Engine(std::unique_ptr<Window>&& window) :
		windowLayer(std::move(window)), inputLayer(&windowLayer.GetWindow().GetInputDevice()), renderLayer(), dataLayer(), sceneLayer(), editorLayer()
	{
		windowLayer.GetWindow().events.Bind(WindowEventType::Close, this, &Engine::Close);
	}

	Engine::~Engine()
	{
		windowLayer.GetWindow().events.Unbind(WindowEventType::Close, this, &Engine::Close);
	}

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

	Engine Engine::engine;

	void Engine::Initialize() noexcept
	{
		// TODO: Load settings from file

		auto window = Window::Create(WindowArgs(TEXT("LimeEngine"), 1080, 720));
		Renderer::Create(RenderOutputArgs(window.get()), RendererArgs{});
		Engine::Initialize(std::move(window));
	}

	void Engine::Initialize(const WindowArgs& windowArgs, const RendererArgs& renderArgs) noexcept
	{
		auto window = Window::Create(windowArgs);
		Renderer::Create(RenderOutputArgs(window.get()), renderArgs);
		Engine::Initialize(std::move(window));
	}

	void Engine::Initialize(std::unique_ptr<Window>&& window) noexcept
	{
		engine.windowLayer.SetWindow(std::move(window));
		engine.inputLayer.SetInputDevice(&engine.windowLayer.GetWindow().GetInputDevice());
		engine.windowLayer.GetWindow().events.Bind(WindowEventType::Close, &engine, &Engine::Close);
	}

	Engine& Engine::GetEngine() noexcept
	{
		return engine;
	}
}
