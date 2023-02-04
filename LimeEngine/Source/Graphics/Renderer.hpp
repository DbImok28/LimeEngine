#pragma once
#include "RenderPreset.hpp"
#include "RenderQueue.hpp"
#include "GraphicFactory.hpp"
#include "Scene/CameraComponent.hpp"
#include "Scene/MeshComponent.hpp"

namespace LimeEngine
{
	class Renderer
	{
	public:
		explicit Renderer(Window* window);
		virtual ~Renderer() = default;
		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;

	protected:
		virtual void PreProcessing() = 0;
		virtual void PostProcessing() = 0;

	public:
		void Render(RenderPreset& preset);
		virtual void Draw(Mesh& mesh, const TempTransformMatrix& transformMatrix) = 0;
		virtual const GraphicFactory* GetGraphicFactory() const noexcept = 0;

		void AddToRender(IDrawable* drawable);
		void RemoveFromRender(const IDrawable* drawable) noexcept;

	protected:
		CameraComponent* camera = nullptr;
		Window* window;
		RenderQueue renderQueue;
	};
}