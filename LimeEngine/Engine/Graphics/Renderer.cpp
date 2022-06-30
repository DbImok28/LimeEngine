#include "Renderer.hpp"

namespace LimeEngine
{
	Renderer::Renderer(RenderingSystem* renderSystem, Window* window) : renderSystem(renderSystem), window(window)
	{
		renderSystem->Initialize(*window);
	}

	void Renderer::AddToRender(MeshComponent* meshComponent)
	{
		renderSystem->AddToRender(meshComponent);
	}

	void Renderer::RemoveFromRender(const MeshComponent* meshComponent) noexcept
	{
		renderSystem->RemoveFromRender(meshComponent);
	}

	std::optional<int> Renderer::Process()
	{
		return window->ProcessMessages();
	}

	void Renderer::Render(const CameraComponent* cameraComponent)
	{
		renderSystem->Render(cameraComponent);
	}
}