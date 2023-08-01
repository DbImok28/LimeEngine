// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "GraphicFactory.hpp"
#include "Material.hpp"

namespace LimeEngine
{
	class MeshSegment
	{
		LE_DELETE_COPY(MeshSegment);

	public:
		MeshSegment() = default;
		MeshSegment(MeshSegment&& other) noexcept;
		MeshSegment& operator=(MeshSegment&& other) noexcept;
		MeshSegment(const GraphicFactory* graphicFactory, const std::vector<Vertex>& vertices, const std::vector<uint>& indices);
		MeshSegment(const GraphicFactory* graphicFactory, const std::pair<std::vector<Vertex>, std::vector<uint>>& verticesAndIndices);

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