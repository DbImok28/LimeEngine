#include "Renderer.hpp"

namespace LimeEngine
{
	Renderer::Renderer(RenderingSystem* renderSystem, Window* window) : renderSystem(renderSystem), window(window)
	{
		renderSystem->Initialize(*window);
	}

	void Renderer::AddToRender(MeshComponent* meshComponent) noexcept
	{
		renderSystem->AddToRender(meshComponent);
	}

	bool Renderer::RemoveFromRender(const MeshComponent* meshComponent) noexcept
	{
		return renderSystem->RemoveFromRender(meshComponent);
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