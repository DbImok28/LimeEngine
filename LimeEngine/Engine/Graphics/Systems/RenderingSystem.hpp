#pragma once
#include "../../Window/Window.hpp"
#include "../../Scene/CameraComponent.hpp"
#include "../../Scene/MeshComponent.hpp"

namespace LimeEngine
{
	class RenderingSystem
	{
		RenderingSystem(const RenderingSystem&) = delete;
		RenderingSystem(RenderingSystem&&) noexcept = delete;
		RenderingSystem& operator=(const RenderingSystem&) = delete;
		RenderingSystem& operator=(RenderingSystem&&) noexcept = delete;

	public:
		RenderingSystem() = default;
		virtual ~RenderingSystem() = default;

		virtual void Initialize(const Window& window) = 0;
		virtual void Render(const CameraComponent* cameraComponent) = 0;
		virtual void AddToRender(MeshComponent* meshComponent) noexcept = 0;
		virtual bool RemoveFromRender(const MeshComponent* meshComponent) noexcept = 0;
	};
}