#include "Mesh.hpp"

namespace LimeEngine
{
	Mesh::Mesh(const std::string& gamePath, const GraphicFactory* graphicFactory, const std::vector<Vertex>& vertices, const std::vector<uint>& indices) :
		GameResource(gamePath), vertices(vertices), indices(indices), meshRenderData(graphicFactory->CreateMeshRenderData(vertices, indices))
	{}

	void Mesh::SetMaterial(Material* material) noexcept
	{
		this->material = material;
	}

	void Mesh::BindRenderData(Material* material, const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix)
	{
		meshRenderData->BindData(material, cameraComponent, transformMatrix);
	}

	uint Mesh::IndicesCount() const noexcept
	{
		return static_cast<uint>(indices.size());
	}

	Material* Mesh::GetMaterial() const noexcept
	{
		return material;
	}

	const std::vector<Vertex>& Mesh::GetVertices() const noexcept
	{
		return vertices;
	}

	const std::vector<uint>& Mesh::GetIndices() const noexcept
	{
		return indices;
	}
}