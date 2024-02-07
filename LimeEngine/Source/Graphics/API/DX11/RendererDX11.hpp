// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Graphics/Renderer.hpp"
#include "RenderContextDX11.hpp"
#include "GraphicFactoryDX11.hpp"

namespace LimeEngine
{
	class RendererDX11 : public Renderer
	{
		friend class BindableDX11;
		LE_DELETE_MOVE_COPY(RendererDX11)

	public:
		explicit RendererDX11(Window& window, DisplayMode mode = DisplayMode::Windowed, bool defaultFullscreenModeIsExclusive = false);
		virtual ~RendererDX11();

	public:
		virtual void Draw(Mesh& mesh, const TempTransformMatrix& transformMatrix) override;
		void Resize(uint width, uint height);
		void CreateAllBuffers();
		void DestroyAllBuffers();

	private:
		void Init(DisplayMode mode);

		void Render() override;
		void PreProcessing();
		void PostProcessing();

	public:
		virtual const GraphicFactory* GetGraphicFactory() const noexcept override;
		virtual std::string GetVideoAdapterName() const noexcept override;

	public:
		RenderContextDX11 context;

	private:
		GraphicFactoryDX11 graphicFactory;
	};
}