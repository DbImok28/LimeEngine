#pragma once
#include <vector>
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "ConstantBuffer.hpp"
#include "../../../Scene/MeshComponent.hpp"
#include "../../../Scene/CameraComponent.hpp"

namespace LimeEngine
{
	using namespace DirectX;

	class MeshRenderDataDX11
	{
	public:
		MeshRenderDataDX11(ID3D11Device* device, ID3D11DeviceContext* deviceContext, MeshComponent* meshComponent);
		void InitializeBuffers();
		void ApplyMaterial();
		void UpdateCB(const CameraComponent* cameraComponent) noexcept;
		void Draw(const CameraComponent* cameraComponent);

		MeshComponent* meshComponent = nullptr;

	private:
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* deviceContext = nullptr;
		ConstantBuffer<CB_VS_Coordinates> cbCoordinates;
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
	};
}