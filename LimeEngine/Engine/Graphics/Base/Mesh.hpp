#pragma once
#include <vector>
#include "GraphicFactory.hpp"
#include "Material.hpp"

namespace LimeEngine
{
	class Mesh
	{
	public:
		Mesh(const GraphicFactory* graphicFactory, const std::vector<Vertex>& vertices, const std::vector<uint>& indices, size_t id);
		void SetMaterial(Material* material) noexcept;
		void BindRenderData(Material* material, const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix);
		uint IndicesCount() const noexcept;
		Material* GetMaterial() const noexcept;
		const std::vector<Vertex>& GetVertices() const noexcept;
		const std::vector<uint>& GetIndices() const noexcept;
		const size_t& GetId() const noexcept;

	public:
		std::unique_ptr<MeshRenderData> meshRenderData;

	private:
		std::vector<Vertex> vertices;
		std::vector<uint> indices;
		size_t id;
		Material* material = nullptr;
	};
}