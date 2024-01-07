// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "RendererDX11.hpp"
#include "Scene/Components/MeshComponent.hpp"
#include "Graphics/Mesh.hpp"
#include "RenderOutputDX11.hpp"

namespace LimeEngine
{
	RendererDX11::RendererDX11(Window& window, DisplayMode mode, bool defaultFullscreenModeIsExclusive) :
		Renderer(std::make_unique<WindowRenderOutputDX11>(*this, window, defaultFullscreenModeIsExclusive)), graphicFactory(*this)
	{
		Init(mode);
		RuntimeEditor::Init(window.GetHandle(), context.GetDevice(), context.GetDeviceContext());
	}

	RendererDX11::~RendererDX11()
	{
		renderOutput->SetDisplayMode(DisplayMode::Windowed);
		RuntimeEditor::Destroy();
	}

	void RendererDX11::Resize(uint width, uint height)
	{
		LE_CORE_LOG_TRACE("Resize renderer(width: {}, height: {})", width, height);
		CreateAllBuffers();
	}

	void RendererDX11::CreateAllBuffers()
	{
		uint width = renderOutput->GetWidth();
		uint height = renderOutput->GetHeight();

		renderOutput->Init();
		context.CreateDepthStencil(width, height);
		renderOutput->Bind();
		context.CreateDepthStencilState();
		context.CreateViewport(width, height);
	}

	void RendererDX11::DestroyAllBuffers()
	{
		context.DestroyRenderTargetView();
		context.DestroyDepthStencilView();
		context.DestroyDepthStencilBuffer();
		renderOutput->Destroy();
		context.Flush();
	}

	void RendererDX11::Init(DisplayMode mode)
	{
		context.CreateDevice();
		if (mode == DisplayMode::FullscreenExclusive)
		{
			renderOutput->Init();
			renderOutput->SetDisplayMode(mode);
		}
		else
		{
			CreateAllBuffers();
		}
		context.CreateRasterizerState();
		context.CreateSamplerState();
	}

	void RendererDX11::Draw(Mesh& mesh, const TempTransformMatrix& transformMatrix)
	{
		for (auto& segment : mesh.segments)
		{
			if (!(camera && segment.GetMaterial())) return;
			segment.BindRenderData(segment.GetMaterial().get(), camera, transformMatrix);
			context.DrawIndexed(segment.IndicesCount());
		}
	}

	void RendererDX11::Render()
	{
		if (!camera) return;
		PreProcessing();
		renderQueue.Draw(*this);
		PostProcessing();
	}

	void RendererDX11::PreProcessing()
	{
		float bgcolor[] = { 0.92f, 0.24f, 0.24f, 1.0f };
		context.SetRenderTargets();
		context.ClearRenderTargetView(bgcolor);
		context.ClearDepthStencilView();

		context.SetTriangleTopology();
		context.SetStates();
	}

	void RendererDX11::PostProcessing()
	{
		RuntimeEditor::Render();
		renderOutput->Present();
	}

	const GraphicFactory* RendererDX11::GetGraphicFactory() const noexcept
	{
		return &graphicFactory;
	}
}