#include "Renderer.hpp"

namespace LimeEngine
{
	Renderer::Renderer(RenderingSystem* renderingSystem, Window* window) : renderingSystem(renderingSystem), window(window)
	{
		renderingSystem->Initialize(*window);
	}

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

	void Renderer::SetInputCamera(CameraComponent* cameraComponent)
	{
		renderingSystem->SetInputCamera(cameraComponent);
	}

	void Renderer::Render()
	{
		if (!renderingSystem) return;
		renderingSystem->PreProcessing();
		renderQueue.Draw(*renderingSystem);
		renderingSystem->PostProcessing();
	}
}