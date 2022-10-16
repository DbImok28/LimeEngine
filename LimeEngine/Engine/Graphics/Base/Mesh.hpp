#pragma once
#include <vector>
#include "GraphicFactory.hpp"
#include "Material.hpp"

namespace LimeEngine
{
	class Mesh : public GameResource
	{
	public:
		Mesh(const ResourcePath& resourcePath, const GraphicFactory* graphicFactory, const std::vector<Vertex>& vertices, const std::vector<uint>& indices);

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
}