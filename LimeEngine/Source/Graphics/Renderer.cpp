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

	void Renderer::Render(RenderPreset& preset)
	{
		if (!(camera = preset.camera)) return;
		PreProcessing();
		renderQueue.Draw(*this);
		PostProcessing();
	}
}