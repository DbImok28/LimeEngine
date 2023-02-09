#pragma once
#include "lepch.hpp"
#include "RenderLayer.hpp"

namespace LimeEngine
{
	RenderLayer::RenderLayer(Engine* engine, std::unique_ptr<Renderer>&& renderer, Window& window) : EngineLayer(engine), renderer(std::move(renderer)) {}

	void RenderLayer::Update()
	{
		renderer->Render();
	}

	const CameraComponent* RenderLayer::GetRenderCamera() const noexcept
	{
		return renderer->GetCamera();
	}

	void RenderLayer::SetRenderCamera(CameraComponent* camera) noexcept
	{
		renderer->SetCamera(camera);
	}

	void RenderLayer::AddToRender(IDrawable* drawable)
	{
		renderer->AddToRender(drawable);
	}

	void RenderLayer::RemoveFromRender(const IDrawable* drawable) noexcept
	{
		renderer->RemoveFromRender(drawable);
	}

	const GraphicFactory* RenderLayer::GetGraphicFactory() noexcept
	{
		return renderer->GetGraphicFactory();
	}
}