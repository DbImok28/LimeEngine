#include "Engine.hpp"

namespace LimeEngine
{
	Engine::Engine(EngineIO&& engineIO) : gameDataManager(this, engineIO.renderIO.renderer->GetGraphicFactory()), scene(this)
	{
		this->engineIO.push_back(std::move(engineIO));
	}

	int Engine::Start()
	{
		timer.Start();
		std::optional<int> exitCode = 0;
		while (true)
		{
			deltaTime = timer.ElapsedTime();
			timer.Restart();
			if (exitCode = WindowProcessing()) return *exitCode;
			if (exitCode = EngineProcessing()) return *exitCode;
			RenderProcessing();
		}
	}

	std::optional<int> Engine::EngineProcessing()
	{
		scene.UpdateScene();
		return {};
	}

	std::optional<int> Engine::WindowProcessing()
	{
		std::optional<int> exitCode = 0;
		for (auto it = std::begin(engineIO); it != std::end(engineIO);)
		{
			if (exitCode = it->Process())
			{
				if (*exitCode != 0)
				{
					return *exitCode;
				}
				else
				{
					it = engineIO.erase(it);
				}
			}
			else
			{
				++it;
			}
		}
		if (exitCode.has_value() && *exitCode != 0) return exitCode;
		if (engineIO.size() > 0) return {};
		return 0;
	}

	void Engine::RenderProcessing()
	{
		for (auto& io : engineIO)
		{
			io.Render();
		}
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