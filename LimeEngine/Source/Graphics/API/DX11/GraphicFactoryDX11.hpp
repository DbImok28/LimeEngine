// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Graphics/GraphicFactory.hpp"

namespace LimeEngine
{
	class RendererDX11;

	class GraphicFactoryDX11 : public GraphicFactory
	{
	public:
		explicit GraphicFactoryDX11(RendererDX11& renderer) : renderer(renderer) {}

		virtual std::unique_ptr<MeshRenderData> CreateMeshRenderData(const std::vector<Vertex>& vertices, const std::vector<uint>& indices) const override;
		virtual std::unique_ptr<IBindable> CreateVertexShader(const FPath& filePath, MaterialType materialType) const override;
		virtual std::unique_ptr<IBindable> CreatePixelShader(const FPath& filePath) const override;
		virtual std::unique_ptr<Texture2D> CreateTexture2D(const ResourcePath& resourcePath, const FPath& filePath, TextureType type) const override;
		virtual std::unique_ptr<MaterialBase> CreateMaterial(
			const ResourcePath& resourcePath, std::unique_ptr<IBindable>&& vertexShader, std::unique_ptr<IBindable>&& pixelShader, MaterialType type) const override;
		virtual std::unique_ptr<WindowRenderOutput> CreateRenderOutput(Window& window) const override;

	private:
		RendererDX11& renderer;
	};
}