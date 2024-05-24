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
	class RendererArgs
	{
	};

	class Renderer
	{
		LE_DELETE_MOVE_COPY(Renderer)

	public:
		static void Initialize(const RenderOutputArgs& renderOutputArgs, const RendererArgs& rendererArgs);

	public:
		Renderer() noexcept = default;
		virtual ~Renderer() = default;

	public:
		virtual void Init(const RenderOutputArgs& renderOutputArgs, const RendererArgs& rendererArgs) = 0;
		virtual void Render() = 0;
		virtual void Draw(Mesh& mesh, const TempTransformMatrix& transformMatrix) = 0;

		const CameraComponent* GetCamera() const noexcept;
		void SetCamera(CameraComponent* camera) noexcept;

		DisplayMode GetDisplayMode() const noexcept;
		void SetDisplayMode(DisplayMode mode);
		float GetWidth() const noexcept;
		float GetHeight() const noexcept;

		void AddToRender(IDrawable* drawable);
		void RemoveFromRender(const IDrawable* drawable) noexcept;

		virtual RenderOutput& GetRenderOutput() noexcept = 0;
		virtual const RenderOutput& GetRenderOutput() const noexcept = 0;

	protected:
		CameraComponent* camera = nullptr;
		RenderQueue renderQueue;

	public:
		inline static Renderer& GetRenderer() noexcept
		{
			return *renderer.get();
		}
		template <typename T>
		inline static T& GetRenderer() noexcept
		{
			return *reinterpret_cast<T*>(renderer.get());
		}

	private:
		static std::unique_ptr<Renderer> renderer;
	};
}
