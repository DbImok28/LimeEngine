// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "RendererDX11.hpp"
#include "RenderAPIDX11.hpp"
#include "Scene/Components/MeshComponent.hpp"
#include "Graphics/Mesh.hpp"
#include "RenderOutputDX11.hpp"

namespace LimeEngine
{
	void RendererDX11::Init(const RenderOutputArgs& renderOutputArgs, const RendererArgs& rendererArgs)
	{
		renderOutput.Init(renderOutputArgs);
		CreateAllBuffers();
	}

	RendererDX11::~RendererDX11()
	{
		GetRenderOutput().SetDisplayMode(DisplayMode::Windowed);
		RuntimeEditor::Destroy();
	}

	void RendererDX11::Resize(uint width, uint height)
	{
		LE_CORE_LOG_TRACE("Resize renderer(width: {}, height: {})", width, height);
		viewport.SetSize(width, height);
	}

	void RendererDX11::CreateAllBuffers()
	{
		viewport.Initialize(GetRenderOutput().GetWidth(), GetRenderOutput().GetHeight());
	}

	void RendererDX11::SetTriangleTopology()
	{
		RenderAPI::GetRenderAPI<RenderAPIDX11>().GetContext().SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void RendererDX11::Draw(Mesh& mesh, const TempTransformMatrix& transformMatrix)
	{
		for (auto& segment : mesh.segments)
		{
			if (!(camera && segment.GetMaterial())) return;
			segment.BindRenderData(segment.GetMaterial().get(), camera, transformMatrix);
			RenderAPI::GetRenderAPI<RenderAPIDX11>().GetContext().DrawIndexed(segment.IndicesCount());
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
		//context.SetRenderTargets();
		auto& windowRT = renderOutput.GetRenderTarget();
		auto& windowDSB = renderOutput.GetDepthStencilBuffer();

		viewport.Bind();
		windowRT.Bind(&windowDSB);
		windowRT.Clear(bgcolor);
		windowDSB.Clear();

		SetTriangleTopology();
		depthStencilState.Bind();
		rasterizerState.Bind();
		samplerState.Bind();
	}

	void RendererDX11::PostProcessing()
	{
		RuntimeEditor::Render();
		GetRenderOutput().Present();
	}
}
