#pragma once
#include "Material.hpp"
#include "../../Base/Vertex.hpp"
#include "../Systems/DX11/RenderingSystemDX11.hpp"
#include "../Systems/DX11/Buffers.hpp"
#include "../Systems/DX11/ConstantBuffers.hpp"

namespace LimeEngine
{
	class MeshRenderDataDX11
	{
	public:
		MeshRenderDataDX11(RenderingSystemDX11& renderer, const std::vector<Vertex>& vertices, const std::vector<uint>& indices);
		void InitializeBuffers(const std::vector<Vertex>& vertices, const std::vector<uint>& indices);
		void ApplyMaterial(Material* material);
		void ApplyTransform(const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix) noexcept;
		void ApplyBuffers() noexcept;
		void ApplyAll(Material* material, const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix);

	public:
		RenderingSystemDX11& renderer;
		VertexShaderConstantBuffer<VSTransformConstantBuffer> transformConstantBuffer;
		VertexBuffer<Vertex> vertexBuffer;
		IndexBuffer indexBuffer;
	};
}