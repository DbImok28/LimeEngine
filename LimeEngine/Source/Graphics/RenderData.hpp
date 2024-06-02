// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Material.hpp"
#include "Scene/Components/CameraComponent.hpp"
#include "Base/Vertex.hpp"
#include "Buffers.hpp"
#include "ConstantBuffers.hpp"

namespace LimeEngine
{
	class MeshRenderData
	{
	public:
		MeshRenderData(const std::vector<Vertex>& vertices, const std::vector<uint>& indices) :
			vertexBuffer(VertexBuffer::Create(vertices)), indexBuffer(IndexBuffer::Create(indices)), transformConstantBuffer()
		{}
		MeshRenderData(MeshRenderData&& other) noexcept;
		MeshRenderData& operator=(MeshRenderData&& other) noexcept;
		virtual ~MeshRenderData() = default;

		void ApplyMaterial(Material* material);
		void ApplyTransform(const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix);
		void ApplyBuffers() noexcept;
		void BindData(Material* material, const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix);

	public:
		SRef<VertexBuffer> vertexBuffer;
		SRef<IndexBuffer> indexBuffer;
		ConstantBuffer<VSTransformConstantBuffer> transformConstantBuffer;
	};
}
