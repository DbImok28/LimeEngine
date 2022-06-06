#pragma once
#include <vector>
#include "RenderingSystemDX11.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "ConstantBuffer.hpp"
#include "../../../Scene/CameraComponent.hpp"

namespace LimeEngine
{
	using namespace DirectX;

	class Mesh;

	class MeshDX11
	{
	public:
		MeshDX11(const RenderingSystemDX11& renderer, Mesh* mesh);
		void InitializeBuffers();
		void ApplyMaterial();
		void UpdateCB(const CameraComponent* cameraComponent, const TempTransformMatrix worldMatrix) noexcept;
		void Draw(const CameraComponent* cameraComponent, const TempTransformMatrix worldMatrix);

	private:
		Mesh* mesh = nullptr;

		const RenderingSystemDX11& renderer;
		ConstantBuffer<CB_VS_Coordinates> cbCoordinates;
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
	};
}