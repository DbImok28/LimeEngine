#pragma once
#include "Material.hpp"
#include "../Systems/DX11/RenderingSystemDX11.hpp"
#include "../Systems/DX11/VertexBuffer.hpp"
#include "../Systems/DX11/IndexBuffer.hpp"
#include "../Systems/DX11/ConstantBuffer.hpp"

namespace LimeEngine
{
	class MeshRenderData
	{
	public:
		MeshRenderData(const RenderingSystemDX11* renderer, const std::vector<Vertex>& vertices, const std::vector<uint>& indices);
		void InitializeBuffers(const std::vector<Vertex>& vertices, const std::vector<uint>& indices);
		void ApplyMaterial(Material* material);
		void ApplyTransform(const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix) noexcept;
		void ApplyBuffers() const noexcept;
		void ApplyTransformAndMaterial(Material* material, const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix);

	public:
		const RenderingSystemDX11* renderer;
		ConstantBuffer<CB_VS_Coordinates> cbCoordinates;
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
	};
}