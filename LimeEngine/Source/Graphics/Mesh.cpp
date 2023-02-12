#include "lepch.hpp"
#include "Mesh.hpp"

namespace LimeEngine
{
	MeshSegment::MeshSegment(MeshSegment&& other) noexcept
	{
		vertices = std::move(other.vertices);
		indices = std::move(other.indices);
		material = std::move(other.material);
		meshRenderData = std::move(other.meshRenderData);
	}

	MeshSegment& MeshSegment::operator=(MeshSegment&& other) noexcept
	{
		if (this != &other)
		{
			vertices = std::move(other.vertices);
			indices = std::move(other.indices);
			material = std::move(other.material);
			meshRenderData = std::move(other.meshRenderData);

			other.vertices = {};
			other.indices = {};
			other.material = nullptr;
			other.meshRenderData = nullptr;
		}
		return *this;
	}

	MeshSegment::MeshSegment(const GraphicFactory* graphicFactory, const std::vector<Vertex>& vertices, const std::vector<uint>& indices) :
		vertices(vertices), indices(indices), meshRenderData(graphicFactory->CreateMeshRenderData(vertices, indices))
	{}

	MeshSegment::MeshSegment(const GraphicFactory* graphicFactory, const std::pair<std::vector<Vertex>, std::vector<uint>>& verticesAndIndices) :
		vertices(vertices), indices(indices), meshRenderData(graphicFactory->CreateMeshRenderData(verticesAndIndices.first, verticesAndIndices.second))
	{}

	void MeshSegment::SetMaterial(Material* material) noexcept
	{
		this->material = material;
	}

	void MeshSegment::BindRenderData(Material* material, const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix)
	{
		meshRenderData->BindData(material, cameraComponent, transformMatrix);
	}

	uint MeshSegment::IndicesCount() const noexcept
	{
		return static_cast<uint>(indices.size());
	}

	Material* MeshSegment::GetMaterial() const noexcept
	{
		return material;
	}

	const std::vector<Vertex>& MeshSegment::GetVertices() const noexcept
	{
		return vertices;
	}

	const std::vector<uint>& MeshSegment::GetIndices() const noexcept
	{
		return indices;
	}

	Mesh::Mesh(const ResourcePath& resourcePath, std::vector<MeshSegment>&& segments) : GameResource(resourcePath), segments(std::move(segments)) {}

	Mesh::Mesh(const ResourcePath& resourcePath, const GraphicFactory* graphicFactory, const std::vector<std::pair<std::vector<Vertex>, std::vector<uint>>>& segmentData) :
		GameResource(resourcePath), segments()
	{
		segments.reserve(segmentData.size());
		for (auto& [vertices, indices] : segmentData)
		{
			segments.emplace_back(graphicFactory, vertices, indices);
		}
	}

	Mesh::Mesh(const ResourcePath& resourcePath, const GraphicFactory* graphicFactory, const std::vector<Vertex>& vertices, const std::vector<uint>& indices) :
		GameResource(resourcePath), segments()
	{
		segments.emplace_back(graphicFactory, vertices, indices);
	}
}