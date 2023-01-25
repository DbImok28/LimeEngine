#include "Renderer.hpp"

namespace LimeEngine
{
	Renderer::Renderer(Window* window) : window(window) {}

	void Renderer::AddToRender(IDrawable* drawable)
	{
		renderQueue.Add(drawable);
	}

	void Renderer::RemoveFromRender(const IDrawable* drawable) noexcept
	{
		renderQueue.Remove(drawable);
	}

	std::optional<int> Renderer::Process()
	{
		auto result = window->ProcessMessages();
		window->inputDevice.Update();
		return result;
	}

	void Renderer::Render()
	{
		PreProcessing();
		renderQueue.Draw(*this);
		PostProcessing();
	}
}