#pragma once
#include <memory>
#include "Systems/RenderingSystem.hpp"
#include "../Scene/CameraComponent.hpp"
#include "../Scene/MeshComponent.hpp"
#include "Base/RenderQueue.hpp"

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
		void SetInputCamera(CameraComponent* cameraComponent);
		void Render();

		void AddToRender(IDrawable* drawable);
		void RemoveFromRender(const IDrawable* drawable) noexcept;
		// TODO: private:
	public:
		RenderingSystem* renderingSystem;
		Window* window;
		RenderQueue renderQueue;
	};
}