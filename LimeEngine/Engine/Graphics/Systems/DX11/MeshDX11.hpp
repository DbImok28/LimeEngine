#pragma once
#include <vector>
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "ConstantBuffer.hpp"
#include "../../../Scene/CameraComponent.hpp"

namespace LimeEngine
{
	using namespace DirectX;

	class MeshComponent;
	class Mesh;
	class Material;

	class MeshDX11
	{
	public:
		MeshDX11(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Mesh* mesh);
		void InitializeBuffers();
		void ApplyMaterial();
		void UpdateCB(const CameraComponent* cameraComponent, const TempTransformMatrix worldMatrix) noexcept;
		void Draw(const CameraComponent* cameraComponent, const TempTransformMatrix worldMatrix);

	private:
		Mesh* mesh = nullptr;

		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* deviceContext = nullptr;
		ConstantBuffer<CB_VS_Coordinates> cbCoordinates;
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
	};
}