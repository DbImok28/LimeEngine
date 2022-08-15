#pragma once
#include "../../Base/GraphicFactory.hpp"

namespace LimeEngine
{
	class RenderingSystemDX11;

	class GraphicFactoryDX11 : public GraphicFactory
	{
	public:
		GraphicFactoryDX11(RenderingSystemDX11& renderingSystem) : renderingSystem(renderingSystem) {}
		virtual ~GraphicFactoryDX11() override = default;

		virtual std::unique_ptr<MeshRenderData> CreateMeshRenderData(const std::vector<Vertex>& vertices, const std::vector<uint>& indices) const override;
		virtual std::unique_ptr<IBindable> CreateVertexShader(std::wstring path, MaterialType materialType) const override;
		virtual std::unique_ptr<IBindable> CreatePixelShader(std::wstring path) const override;
		virtual std::unique_ptr<Texture2D> CreateTexture2D(std::wstring path, TextureType type, size_t id) const override;

	private:
		RenderingSystemDX11& renderingSystem;
	};
}