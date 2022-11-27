#pragma once
#include <vector>
#include "GraphicFactory.hpp"
#include "Material.hpp"

namespace LimeEngine
{
	class MeshSegment
	{
	public:
		MeshSegment() = default;
		MeshSegment(const GraphicFactory* graphicFactory, const std::vector<Vertex>& vertices, const std::vector<uint>& indices);
		MeshSegment(const GraphicFactory* graphicFactory, const std::pair<std::vector<Vertex>, std::vector<uint>>& verticesAndIndices);
		MeshSegment(const MeshSegment&) = delete;
		MeshSegment& operator=(const MeshSegment&) = delete;
		MeshSegment(MeshSegment&& other) noexcept
		{
			vertices = std::move(other.vertices);
			indices = std::move(other.indices);
			material = std::move(other.material);
			meshRenderData = std::move(other.meshRenderData);
		}
		MeshSegment& operator=(MeshSegment&& other) noexcept
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

		void SetMaterial(Material* material) noexcept;
		void BindRenderData(Material* material, const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix);
		uint IndicesCount() const noexcept;
		Material* GetMaterial() const noexcept;
		const std::vector<Vertex>& GetVertices() const noexcept;
		const std::vector<uint>& GetIndices() const noexcept;

	private:
		std::vector<Vertex> vertices;
		std::vector<uint> indices;
		Material* material = nullptr;

	public:
		std::unique_ptr<MeshRenderData> meshRenderData;
	};

	class Mesh : public GameResource
	{
	public:
		Mesh(const ResourcePath& resourcePath, std::vector<MeshSegment>&& segments);
		Mesh(const ResourcePath& resourcePath, const GraphicFactory* graphicFactory, const std::vector<std::pair<std::vector<Vertex>, std::vector<uint>>>& segmentData);
		Mesh(const ResourcePath& resourcePath, const GraphicFactory* graphicFactory, const std::vector<Vertex>& vertices, const std::vector<uint>& indices);

	public:
		std::vector<MeshSegment> segments;
	};
}