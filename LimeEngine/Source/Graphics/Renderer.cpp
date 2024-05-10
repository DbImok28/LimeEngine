// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Renderer.hpp"
#include "RenderAPI.hpp"

namespace LimeEngine
{
	std::unique_ptr<Renderer> Renderer::renderer = RenderAPI::CreateRenderer(RenderAPI::DefaultRenderAPI);

	void Renderer::Create(const RenderOutputArgs& renderOutputArgs, const RendererArgs& rendererArgs)
	{
		renderer->Init(renderOutputArgs, rendererArgs);
	}

	const CameraComponent* Renderer::GetCamera() const noexcept
	{
		return camera;
	}

	void Renderer::SetCamera(CameraComponent* camera) noexcept
	{
		this->camera = camera;
	}

	DisplayMode Renderer::GetDisplayMode() const noexcept
	{
		return GetRenderOutput().GetDisplayMode();
	}

	void Renderer::SetDisplayMode(DisplayMode mode)
	{
		GetRenderOutput().SetDisplayMode(mode);
	}

	float Renderer::GetWidth() const noexcept
	{
		return static_cast<float>(GetRenderOutput().GetWidth());
	}

	float Renderer::GetHeight() const noexcept
	{
		return static_cast<float>(GetRenderOutput().GetHeight());
	}

	void Renderer::AddToRender(IDrawable* drawable)
	{
		renderQueue.Add(drawable);
	}

	void Renderer::RemoveFromRender(const IDrawable* drawable) noexcept
	{
		renderQueue.Remove(drawable);
	}
}
