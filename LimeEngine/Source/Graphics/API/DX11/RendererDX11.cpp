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
	void RendererDX11::Init(const RenderOutputArgs& renderOutputArgs, const RendererArgs& rendererArgs)
	{
		context.CreateDevice();
		renderOutput.Init(renderOutputArgs);
		CreateAllBuffers();
		context.CreateRasterizerState();
		context.CreateSamplerState();
	}

	RendererDX11::~RendererDX11()
	{
		GetRenderOutput().SetDisplayMode(DisplayMode::Windowed);
		RuntimeEditor::Destroy();
	}

	void RendererDX11::Resize(uint width, uint height)
	{
		LE_CORE_LOG_TRACE("Resize renderer(width: {}, height: {})", width, height);
		CreateAllBuffers();
	}

	void RendererDX11::CreateAllBuffers()
	{
		uint width = GetRenderOutput().GetWidth();
		uint height = GetRenderOutput().GetHeight();

		GetRenderOutput().Create();
		context.CreateDepthStencil(width, height);
		GetRenderOutput().Bind();
		context.CreateDepthStencilState();
		context.CreateViewport(width, height);
	}

	void RendererDX11::DestroyAllBuffers()
	{
		context.DestroyRenderTargetView();
		context.DestroyDepthStencilView();
		context.DestroyDepthStencilBuffer();
		GetRenderOutput().Destroy();
		context.Flush();
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
		GetRenderOutput().Present();
	}

	RenderOutput& RendererDX11::GetRenderOutput() noexcept
	{
		return renderOutput;
	}

	const RenderOutput& RendererDX11::GetRenderOutput() const noexcept
	{
		return renderOutput;
	}

	std::string RendererDX11::GetVideoAdapterName() const noexcept
	{
		return context.GetGraphicAdapter().GetName();
	}
}
