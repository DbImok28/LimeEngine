// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Renderer.hpp"
#include "RenderAPI.hpp"

namespace LimeEngine
{
	void Renderer::Render()
	{
		if (!camera || !renderOutput) return;
		PreProcessing();
		renderQueue.Draw(*this);
		PostProcessing();
	}

	void Renderer::PreProcessing()
	{
		float bgcolor[] = { 0.92f, 0.24f, 0.24f, 1.0f };
		auto& windowRT = renderOutput->GetRenderTarget();
		auto& windowDSB = renderOutput->GetDepthStencilBuffer();

		renderOutput->GetRenderViewport().Bind();
		windowRT.Bind(&windowDSB);
		windowRT.Clear(bgcolor);
		windowDSB.Clear();

		RenderAPI::GetRenderAPI().SetPrimitiveTopology(PrimitiveTopology::TriangleList);
		RenderAPI::GetRenderAPI().BindPipline();
	}

	void Renderer::PostProcessing()
	{
		RuntimeEditor::Render();
		GetRenderOutput().Present();
	}

	void Renderer::Draw(Mesh& mesh, const TempTransformMatrix& transformMatrix)
	{
		for (auto& segment : mesh.segments)
		{
			if (!(camera && segment.GetMaterial())) return;
			segment.BindRenderData(segment.GetMaterial().get(), camera, transformMatrix);

			RenderAPI::GetRenderAPI().DrawIndexed(segment.IndicesCount());
		}
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

	void Renderer::RemoveFromRender(const IDrawable* drawable)
	{
		renderQueue.Remove(drawable);
	}

	void Renderer::SetRenderOutput(URef<RenderOutput>&& renderOutput)
	{
		this->renderOutput = std::move(renderOutput);
	}

	void Renderer::RemoveRenderOutput()
	{
		renderOutput = nullptr;
	}

	RenderOutput& Renderer::GetRenderOutput() noexcept
	{
		return *renderOutput;
	}

	const RenderOutput& Renderer::GetRenderOutput() const noexcept
	{
		return *renderOutput;
	}
}
