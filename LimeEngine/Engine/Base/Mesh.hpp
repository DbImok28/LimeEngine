#pragma once
#include "../Graphics/Buffers/VertexBuffer.hpp"
#include "../Graphics/Buffers/IndexBuffer.hpp"
#include "Material.hpp"
#include "Transform.hpp"
#include "../Scene/CameraObject.hpp"
#include <vector>

namespace LimeEngine
{
	using namespace DirectX;

	class Engine;

	class Mesh
	{
	public:
		Mesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const std::vector<Vertex>& vertices, const std::vector<DWORD>& indices);
		void SetMaterial(Material& material) noexcept;
		void SetMaterial(Material* material) noexcept;
		Material* GetMaterial() const noexcept;
		void InitializeBuffers(ID3D11Device* device);
		void Draw(const CameraObject& camera, TempTransformMatrix worldMatrix);
	private:

		//TempTransformMatrix trasformMatrix;
		Material* material = nullptr;
		ID3D11DeviceContext* deviceContext;

		ConstantBuffer<CB_VS_Coordinates> cbCoordinates;
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
		std::vector<Vertex> vertices;
		std::vector<DWORD> indices;
	};
}