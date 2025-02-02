// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "lepch.hpp"
#include "Graphics/RenderAPI.hpp"
#include "RenderLayer.hpp"
#include "Engine.hpp"

#ifdef LE_DEBUG
	#include "Graphics/API/DX11/ExceptionsDX11.hpp"
#endif

namespace LimeEngine
{
	RenderLayer* RenderLayer::GetRenderLayer()
	{
		return GetEngine()->renderLayer;
	}

	void RenderLayer::Update()
	{
		EngineLayer::Update();
		Renderer::GetRenderer().Render();
	}

	void RenderLayer::DebugUpdate()
	{
		EngineLayer::DebugUpdate();

		auto& renderer = Renderer::GetRenderer();
		if (RuntimeEditor::BeginPanel("Renderer"))
		{
			RuntimeEditor::Text("GPU Name", RenderAPI::GetRenderAPI().GetVideoAdapterName());

			// TODO: Remove
			RuntimeEditor::Text("DXGI Messages:");
			for (auto& message : dxgiErrorInfo.GetAllMessages())
			{
				RuntimeEditor::Text(message);
			}

			RuntimeEditor::EndPanel();
		}

		if (RuntimeEditor::BeginPanel("Window"))
		{
			RuntimeEditor::Text("Width", std::to_string(renderer.GetWidth()));
			RuntimeEditor::Text("Height", std::to_string(renderer.GetHeight()));

			auto winMode = renderer.GetDisplayMode();
			if (winMode == DisplayMode::Windowed || winMode == DisplayMode::FullscreenWindowed)
			{
				if (RuntimeEditor::Button("Change windowed mode to FullscreenExclusive")) { renderer.SetDisplayMode(DisplayMode::FullscreenExclusive); }
			}
			if (winMode == DisplayMode::Windowed)
			{
				if (RuntimeEditor::Button("Change windowed mode to FullscreenWindowed")) { renderer.SetDisplayMode(DisplayMode::FullscreenWindowed); }
			}

			if (winMode == DisplayMode::FullscreenWindowed || winMode == DisplayMode::FullscreenExclusive)
			{
				if (RuntimeEditor::Button("Change windowed mode to Windowed")) { renderer.SetDisplayMode(DisplayMode::Windowed); }
			}
			RuntimeEditor::EndPanel();
		}
	}

	const CameraComponent* RenderLayer::GetRenderCamera() const noexcept
	{
		return Renderer::GetRenderer().GetCamera();
	}

	void RenderLayer::SetRenderCamera(CameraComponent* camera) noexcept
	{
		Renderer::GetRenderer().SetCamera(camera);
	}

	void RenderLayer::AddToRender(IDrawable* drawable)
	{
		Renderer::GetRenderer().AddToRender(drawable);
	}

	void RenderLayer::RemoveFromRender(const IDrawable* drawable)
	{
		Renderer::GetRenderer().RemoveFromRender(drawable);
	}
}
