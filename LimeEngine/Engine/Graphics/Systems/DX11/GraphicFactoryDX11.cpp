#include "GraphicFactoryDX11.hpp"
#include "RendererDX11.hpp"
#include "RenderDataDX11.hpp"
#include "ShadersDX11.hpp"
#include "Texture2DDX11.hpp"

namespace LimeEngine
{
	std::unique_ptr<MeshRenderData> GraphicFactoryDX11::CreateMeshRenderData(const std::vector<Vertex>& vertices, const std::vector<uint>& indices) const
	{
		return std::make_unique<MeshRenderDataDX11>(renderer, vertices, indices);
	}

	std::unique_ptr<IBindable> GraphicFactoryDX11::CreateVertexShader(std::wstring path, MaterialType materialType) const
	{
		return std::make_unique<VertexShaderDX11>(renderer, path, materialType);
	}

	std::unique_ptr<IBindable> GraphicFactoryDX11::CreatePixelShader(std::wstring path) const
	{
		return std::make_unique<PixelShaderDX11>(renderer, path);
	}

	std::unique_ptr<Texture2D> GraphicFactoryDX11::CreateTexture2D(std::wstring path, TextureType type, size_t id) const
	{
		return std::make_unique<Texture2DDX11>(renderer, path, type, id);
	}
}