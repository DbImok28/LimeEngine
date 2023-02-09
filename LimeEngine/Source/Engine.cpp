#include "lepch.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	Engine::Engine(std::unique_ptr<Window>&& window, std::unique_ptr<Renderer>&& renderer) :
		gameDataManager(this, renderer->GetGraphicFactory()), windowLayer(this, std::move(window)), inputLayer(this, windowLayer.GetWindow().GetInputDevice()),
		renderLayer(this, std::move(renderer), windowLayer.GetWindow()), sceneLayer(this)
	{
		windowLayer.GetWindow().events.Bind(WindowEventType::Close, this, &Engine::Close);
	}

	int Engine::Start()
	{
		timer.Start();
		while (!exitCode.has_value())
		{
			deltaTime = timer.ElapsedTime();
			timer.Restart();
			UpdateLayers();
		}
		return *exitCode;
	}

	void Engine::UpdateLayers()
	{
		RuntimeEditor::Processing();
		windowLayer.Update();
		inputLayer.Update();
		sceneLayer.Update();
		renderLayer.Update();
	}

	void Engine::Close(const Event& e)
	{
		this->exitCode = CastEvent<CloseWindowEvent>(e).exitCode;
	}
}