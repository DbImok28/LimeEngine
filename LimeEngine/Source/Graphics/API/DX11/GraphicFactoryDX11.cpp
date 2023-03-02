#include "lepch.hpp"
#include "GraphicFactoryDX11.hpp"
#include "RendererDX11.hpp"
#include "RenderDataDX11.hpp"
#include "ShadersDX11.hpp"
#include "Texture2DDX11.hpp"
#include "RenderOutputDX11.hpp"

namespace LimeEngine
{
	std::unique_ptr<MeshRenderData> GraphicFactoryDX11::CreateMeshRenderData(const std::vector<Vertex>& vertices, const std::vector<uint>& indices) const
	{
		return std::make_unique<MeshRenderDataDX11>(renderer, vertices, indices);
	}

	std::unique_ptr<IBindable> GraphicFactoryDX11::CreateVertexShader(const FPath& filePath, MaterialType materialType) const
	{
		return std::make_unique<VertexShaderDX11>(renderer, filePath, materialType);
	}

	std::unique_ptr<IBindable> GraphicFactoryDX11::CreatePixelShader(const FPath& filePath) const
	{
		return std::make_unique<PixelShaderDX11>(renderer, filePath);
	}

	std::unique_ptr<Texture2D> GraphicFactoryDX11::CreateTexture2D(const ResourcePath& resourcePath, const FPath& filePath, TextureType type) const
	{
		return std::make_unique<Texture2DDX11>(renderer, resourcePath, filePath, type);
	}

	std::unique_ptr<WindowRenderOutput> GraphicFactoryDX11::CreateRenderOutput(Window& window) const
	{
		return std::make_unique<WindowRenderOutputDX11>(renderer, window);
	}
}