#pragma once
#include "../../Base/GraphicFactory.hpp"

namespace LimeEngine
{
	class RendererDX11;

	class GraphicFactoryDX11 : public GraphicFactory
	{
	public:
		explicit GraphicFactoryDX11(RendererDX11& renderer) : renderer(renderer) {}
		virtual ~GraphicFactoryDX11() override = default;

		virtual std::unique_ptr<MeshRenderData> CreateMeshRenderData(const std::vector<Vertex>& vertices, const std::vector<uint>& indices) const override;
		virtual std::unique_ptr<IBindable> CreateVertexShader(std::wstring path, MaterialType materialType) const override;
		virtual std::unique_ptr<IBindable> CreatePixelShader(std::wstring path) const override;
		virtual std::unique_ptr<Texture2D> CreateTexture2D(std::string gamePath, std::wstring filePath, TextureType type) const override;

	private:
		RendererDX11& renderer;
	};
}