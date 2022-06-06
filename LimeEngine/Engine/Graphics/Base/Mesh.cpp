#include "Mesh.hpp"

namespace LimeEngine
{
	Mesh::Mesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const std::vector<Vertex>& vertices, const std::vector<DWORD>& indices, size_t id) :
		vertices(vertices), indices(indices), id(id), renderMesh(device, deviceContext, this) {}

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