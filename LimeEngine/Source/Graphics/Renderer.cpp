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
		return window->ProcessMessages();
	}

	void Renderer::Render()
	{
		PreProcessing();
		renderQueue.Draw(*this);
		PostProcessing();
	}
}