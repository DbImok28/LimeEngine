// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Graphics/Renderer.hpp"
#include "RenderContextDX11.hpp"
#include "RenderOutputDX11.hpp"
#include "RenderStatesDX11.hpp"
#include "RenderViewportDX11.hpp"

namespace LimeEngine
{
	class RendererDX11 final : public Renderer
	{
		friend class BindableDX11;
		LE_DELETE_MOVE_COPY(RendererDX11)

	public:
		RendererDX11(){};
		virtual ~RendererDX11();

	public:
		virtual void Init(const RenderOutputArgs& renderOutputArgs, const RendererArgs& rendererArgs) override;
		virtual void Draw(Mesh& mesh, const TempTransformMatrix& transformMatrix) override;

		void Resize(uint width, uint height);
		void CreateAllBuffers();
		void SetTriangleTopology();

	private:
		void Render() override;
		void PreProcessing();
		void PostProcessing();

	public:
		virtual RenderOutput& GetRenderOutput() noexcept override
		{
			return renderOutput;
		}
		virtual const RenderOutput& GetRenderOutput() const noexcept override
		{
			return renderOutput;
		}

	private:
		WindowRenderOutputDX11 renderOutput;

		DepthStencilStateDX11 depthStencilState;
		RasterizerStateDX11 rasterizerState;
		SamplerStateDX11 samplerState;

		RenderViewportDX11 viewport;
	};
}
