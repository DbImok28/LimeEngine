#pragma once
#include <vector>
#include "MeshRenderDataDX11.hpp"
#include "Material.hpp"
#include "../../Base/Vertex.hpp"

namespace LimeEngine
{
	class Mesh
	{
	public:
		Mesh(RenderingSystemDX11& renderer, const std::vector<Vertex>& vertices, const std::vector<uint>& indices, size_t id);
		void SetMaterial(Material* material) noexcept;
		Material* GetMaterial() const noexcept;
		const std::vector<Vertex>& GetVertices() const noexcept;
		const std::vector<uint>& GetIndices() const noexcept;
		const size_t& GetId() const noexcept;

	public:
		MeshRenderDataDX11 meshRenderData;

	private:
		std::vector<Vertex> vertices;
		std::vector<uint> indices;
		size_t id;
		Material* material = nullptr;
	};
}