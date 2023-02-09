#pragma once
#include "RenderOutput.hpp"
#include "RenderQueue.hpp"
#include "GraphicFactory.hpp"
#include "Scene/CameraComponent.hpp"
#include "Scene/MeshComponent.hpp"

namespace LimeEngine
{
	class Renderer
	{
		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;

	public:
		explicit Renderer(std::unique_ptr<RenderOutput>&& renderOutput);
		virtual ~Renderer() = default;

	public:
		virtual void Render() = 0;
		virtual void Draw(Mesh& mesh, const TempTransformMatrix& transformMatrix) = 0;
		virtual const GraphicFactory* GetGraphicFactory() const noexcept = 0;

		void SetCamera(CameraComponent* camera) noexcept;
		const CameraComponent* GetCamera() noexcept;
		void AddToRender(IDrawable* drawable);
		void RemoveFromRender(const IDrawable* drawable) noexcept;

	protected:
		CameraComponent* camera = nullptr;
		std::unique_ptr<RenderOutput> renderOutput;
		RenderQueue renderQueue;
	};
}