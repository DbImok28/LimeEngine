#pragma once
#include <memory>
#include "../Window/Windows/Main/Window.hpp"
#include "Base/RenderQueue.hpp"
#include "Base/GraphicFactory.hpp"
#include "../Scene/CameraComponent.hpp"
#include "../Scene/MeshComponent.hpp"

namespace LimeEngine
{
	class Renderer
	{
	public:
		Renderer(Window* window);
		virtual ~Renderer() = default;
		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;

		void Render();
		std::optional<int> Process();

	protected:
		virtual void PreProcessing() = 0;
		virtual void PostProcessing() = 0;

	public:
		virtual void Draw(Mesh& mesh, const TempTransformMatrix& transformMatrix) = 0;
		virtual void SetInputCamera(CameraComponent* cameraComponent) = 0;
		virtual const GraphicFactory* GetGraphicFactory() const noexcept = 0;

		void AddToRender(IDrawable* drawable);
		void RemoveFromRender(const IDrawable* drawable) noexcept;
		InputDevice& GetInputDevice() const noexcept
		{
			return window->inputDevice;
		}
		Window* GetWindow() const noexcept
		{
			return window;
		}

	private:
		Window* window;
		RenderQueue renderQueue;
	};
}