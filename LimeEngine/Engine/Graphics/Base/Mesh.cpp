#include "Mesh.hpp"

namespace LimeEngine
{
	Mesh::Mesh(const RenderingSystemDX11& renderer, const std::vector<Vertex>& vertices, const std::vector<DWORD>& indices, size_t id) :
		vertices(vertices), indices(indices), id(id), renderMesh(renderer, this)
	{}

	void Mesh::SetMaterial(Material* material) noexcept
	{
		this->material = material;
	}

	Material* Mesh::GetMaterial() const noexcept
	{
		return material;
	}

	const std::vector<Vertex>& Mesh::GetVertices() const noexcept
	{
		return vertices;
	}

	const std::vector<DWORD>& Mesh::GetIndices() const noexcept
	{
		return indices;
	}
}