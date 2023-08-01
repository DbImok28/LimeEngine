// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	Engine::Engine(std::unique_ptr<Window>&& window, std::unique_ptr<Renderer>&& renderer) :
		windowLayer(this, std::move(window)), inputLayer(this, windowLayer.GetWindow().GetInputDevice()), renderLayer(this, std::move(renderer), windowLayer.GetWindow()),
		dataLayer(this, renderLayer.GetGraphicFactory()), sceneLayer(this), editorLayer(this)
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
}