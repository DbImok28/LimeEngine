#pragma once
#include "../../CoreBase.hpp"
#include <memory>
#include "../../Base/Vertex.hpp"
#include "RenderData.hpp"
#include "IBindable.hpp"
#include "Texture2D.hpp"

namespace LimeEngine
{
	class GraphicFactory
	{
	public:
		virtual ~GraphicFactory() = default;
		virtual std::unique_ptr<MeshRenderData> CreateMeshRenderData(const std::vector<Vertex>& vertices, const std::vector<uint>& indices) const = 0;
		virtual std::unique_ptr<IBindable> CreateVertexShader(std::wstring path, MaterialType materialType) const = 0;
		virtual std::unique_ptr<IBindable> CreatePixelShader(std::wstring path) const = 0;
		virtual std::unique_ptr<Texture2D> CreateTexture2D(std::wstring path, TextureType type, size_t id) const = 0;
	};
}