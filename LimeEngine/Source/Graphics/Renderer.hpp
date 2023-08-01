// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "RenderAPI.hpp"
#include "RenderOutput.hpp"
#include "RenderQueue.hpp"
#include "GraphicFactory.hpp"
#include "Scene/Components/CameraComponent.hpp"
#include "Scene/Components/MeshComponent.hpp"

namespace LimeEngine
{
	class Renderer
	{
		LE_DELETE_MOVE_COPY(Renderer)
	public:
		static std::unique_ptr<Renderer> Create(RenderAPI api, Window& window, DisplayMode mode = DisplayMode::Windowed, bool defaultFullscreenModeIsExclusive = false);

	public:
		explicit Renderer(std::unique_ptr<RenderOutput>&& renderOutput);
		virtual ~Renderer() = default;

	public:
		virtual void Render() = 0;
		virtual void Draw(Mesh& mesh, const TempTransformMatrix& transformMatrix) = 0;
		virtual const GraphicFactory* GetGraphicFactory() const noexcept = 0;

		const CameraComponent* GetCamera() const noexcept;
		void SetCamera(CameraComponent* camera) noexcept;
		DisplayMode GetDisplayMode() const noexcept;
		void SetDisplayMode(DisplayMode mode);
		float GetWidth() const noexcept;
		float GetHeight() const noexcept;
		void AddToRender(IDrawable* drawable);
		void RemoveFromRender(const IDrawable* drawable) noexcept;

	protected:
		CameraComponent* camera = nullptr;
		std::unique_ptr<RenderOutput> renderOutput = nullptr;
		RenderQueue renderQueue;
	};
}