#include "lepch.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	Engine::Engine(EngineIO&& engineIO) : gameDataManager(this, engineIO.renderIO.renderer->GetGraphicFactory()), scene(this)
	{
		engineIO.renderIO.renderer->GetWindow()->CloseEvent.Bind(this, &Engine::Close);
		this->engineIO.push_back(std::move(engineIO));
	}

	int Engine::Start()
	{
		timer.Start();
		while (!exitCode.has_value())
		{
			deltaTime = timer.ElapsedTime();
			timer.Restart();
			WindowProcessing();
			EngineProcessing();
			RenderProcessing();
		}
		return *exitCode;
	}

	void Engine::EngineProcessing()
	{
		scene.UpdateScene();
	}

	void Engine::WindowProcessing()
	{
		for (auto it = std::begin(engineIO); it != std::end(engineIO); it++)
		{
			it->Process();
		}
	}

	void Engine::RenderProcessing()
	{
		for (auto& io : engineIO)
		{
			io.Render();
		}
	}

	void Engine::Close(int exitCode)
	{
		this->exitCode = exitCode;
	}

	void Engine::AddToRender(IDrawable* drawable)
	{
		for (auto& io : engineIO)
		{
			io.renderIO.renderer->AddToRender(drawable);
		}
	}

	void Engine::RemoveFromRender(const IDrawable* drawable) noexcept
	{
		for (auto& io : engineIO)
		{
			io.renderIO.renderer->RemoveFromRender(drawable);
		}
	}
}