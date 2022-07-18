#pragma once
#include <vector>
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "ConstantBuffer.hpp"
#include "../../../Scene/CameraComponent.hpp"

namespace LimeEngine
{
	class MeshComponent;
	class RenderingSystemDX11;

	class MeshDX11
	{
	public:
		MeshDX11(const RenderingSystemDX11& renderer, const MeshComponent* meshComponents);
		void AddMeshComponent(const MeshComponent* meshComponent);
		void RemoveMeshComponent(const MeshComponent* meshComponent) noexcept;
		bool Empty() const noexcept;

		void InitializeBuffers();
		void ApplyMaterial(const MeshComponent* meshComponents);
		void ApplyTransform(const CameraComponent* cameraComponent, const MeshComponent* meshComponent) noexcept;
		void Render(const CameraComponent* cameraComponent);

	private:
		const RenderingSystemDX11& renderer;
		std::vector<const MeshComponent*> meshComponents;
		ConstantBuffer<CB_VS_Coordinates> cbCoordinates;
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
	};
}