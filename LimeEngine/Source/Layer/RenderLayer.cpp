// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "lepch.hpp"
#include "RenderLayer.hpp"

namespace LimeEngine
{
	RenderLayer::RenderLayer(Engine* engine, std::unique_ptr<Renderer>&& renderer, Window& window) : EngineLayer(engine), renderer(std::move(renderer)) {}

	void RenderLayer::Update()
	{
		RuntimeEditor::NewPanel("Window");
		RuntimeEditor::Text("Width", std::to_string(renderer->GetWidth()));
		RuntimeEditor::Text("Height", std::to_string(renderer->GetHeight()));

		auto winMode = renderer->GetDisplayMode();
		if (winMode == DisplayMode::Windowed || winMode == DisplayMode::FullscreenWindowed)
		{
			if (RuntimeEditor::Button("Change windowed mode to FullscreenExclusive"))
			{
				renderer->SetDisplayMode(DisplayMode::FullscreenExclusive);
			}
		}
		if (winMode == DisplayMode::Windowed)
		{
			if (RuntimeEditor::Button("Change windowed mode to FullscreenWindowed"))
			{
				renderer->SetDisplayMode(DisplayMode::FullscreenWindowed);
			}
		}

		if (winMode == DisplayMode::FullscreenWindowed || winMode == DisplayMode::FullscreenExclusive)
		{
			if (RuntimeEditor::Button("Change windowed mode to Windowed"))
			{
				renderer->SetDisplayMode(DisplayMode::Windowed);
			}
		}
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