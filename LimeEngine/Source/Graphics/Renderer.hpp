// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "RenderOutput.hpp"
#include "RenderQueue.hpp"
#include "Scene/Components/CameraComponent.hpp"
#include "Scene/Components/MeshComponent.hpp"

namespace LimeEngine
{
	class Renderer
	{
		LE_DELETE_MOVE_COPY(Renderer)

	public:
		Renderer() noexcept = default;

	public:
		void Render();
		void PreProcessing();
		void PostProcessing();

		void Draw(Mesh& mesh, const TempTransformMatrix& transformMatrix);

		const CameraComponent* GetCamera() const noexcept;
		void SetCamera(CameraComponent* camera) noexcept;

		DisplayMode GetDisplayMode() const noexcept;
		void SetDisplayMode(DisplayMode mode);
		float GetWidth() const noexcept;
		float GetHeight() const noexcept;

		void AddToRender(IDrawable* drawable);
		void RemoveFromRender(const IDrawable* drawable);

		//TODO: Add ability to add and Remove RenderOutput
		void SetRenderOutput(std::unique_ptr<RenderOutput>&& renderOutput);
		void RemoveRenderOutput();
		RenderOutput& GetRenderOutput() noexcept;
		const RenderOutput& GetRenderOutput() const noexcept;

	private:
		std::unique_ptr<RenderOutput> renderOutput;

	protected:
		CameraComponent* camera = nullptr;
		RenderQueue renderQueue;

	public:
		inline static Renderer& GetRenderer() noexcept
		{
			return renderer;
		}

	private:
		static Renderer renderer;
	};
}
