#pragma once
#include "../../Window/Windows/Main/Window.hpp"
#include "../../Scene/CameraComponent.hpp"
#include "../Base/GraphicFactory.hpp"

namespace LimeEngine
{
	class Mesh;

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
		virtual void PreProcessing() = 0;
		virtual void PostProcessing() = 0;
		virtual void SetInputCamera(CameraComponent* cameraComponent) = 0;
		virtual const GraphicFactory* GetGraphicFactory() const noexcept = 0;

		virtual void Draw(Mesh& mesh, const TempTransformMatrix& transformMatrix) = 0;
	};
}