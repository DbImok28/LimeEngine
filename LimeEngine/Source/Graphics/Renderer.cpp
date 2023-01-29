#include "lepch.hpp"
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

	void Renderer::Process()
	{
		window->OnUpdate();
		window->GetInputDevice().OnUpdate();
	}

	void Renderer::Render()
	{
		PreProcessing();
		renderQueue.Draw(*this);
		PostProcessing();
	}
}