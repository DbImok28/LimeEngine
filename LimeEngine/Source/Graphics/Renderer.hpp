#pragma once
#include "RenderAPI.hpp"
#include "RenderOutput.hpp"
#include "RenderQueue.hpp"
#include "GraphicFactory.hpp"
#include "Scene/CameraComponent.hpp"
#include "Scene/MeshComponent.hpp"

namespace LimeEngine
{
	class Renderer
	{
		LE_DELETE_MOVE_COPY(Renderer)
	public:
		static std::unique_ptr<Renderer> Create(RenderAPI api, Window& window);

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