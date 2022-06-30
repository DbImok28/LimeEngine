#include "Mesh.hpp"

namespace LimeEngine
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<DWORD>& indices, size_t id) : vertices(vertices), indices(indices), id(id) {}

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
	const size_t& Mesh::GetId() const noexcept
	{
		return id;
	}
}