#include "lepch.hpp"
#include "Renderer.hpp"

namespace LimeEngine
{
	Renderer::Renderer(std::unique_ptr<RenderOutput>&& renderOutput) : renderOutput(std::move(renderOutput)) {}

	void Renderer::SetCamera(CameraComponent* camera) noexcept
	{
		this->camera = camera;
	}

	const CameraComponent* Renderer::GetCamera() noexcept
	{
		return camera;
	}

	void Renderer::AddToRender(IDrawable* drawable)
	{
		renderQueue.Add(drawable);
	}

	void Renderer::RemoveFromRender(const IDrawable* drawable) noexcept
	{
		renderQueue.Remove(drawable);
	}
}