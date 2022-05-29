#pragma once
#include <memory>
#include "../Scene/CameraComponent.hpp"
#include "../Scene/MeshComponent.hpp"
#include "Systems/RenderingSystem.hpp"

namespace LimeEngine
{
	class Renderer
	{
	public:
		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;
		Renderer(RenderingSystem* renderSystem, Window* window);
		std::optional<int> Process();
		void Render(const CameraComponent* cameraComponent);

		void AddToRender(MeshComponent* meshComponent) noexcept;
		bool RemoveFromRender(const MeshComponent* meshComponent) noexcept;
		// TODO: private:
	public:
		RenderingSystem* renderSystem;
		Window* window;
	};
}