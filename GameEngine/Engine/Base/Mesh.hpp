#pragma once
#include "../Graphics/Buffers/VertexBuffer.hpp"
#include "../Graphics/Buffers/IndexBuffer.hpp"
#include "Material.hpp"
#include <vector>

using namespace DirectX;

class Mesh
{
public:
	Mesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const std::vector<Vertex>& vertices, const std::vector<DWORD>& indices, const XMMATRIX& trasformMatrix = XMMatrixIdentity());
	void SetMaterial(Material& material) noexcept;
	void SetMaterial(Material* material) noexcept;

	void InitializeBuffers(ID3D11Device* device);
	const XMMATRIX& GetTransformMatrix() const noexcept;
	void Draw();
private:

	Material* material = nullptr;

	ID3D11DeviceContext* deviceContext;
	XMMATRIX trasformMatrix;
	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;
	std::vector<Vertex> vertices;
	std::vector<DWORD> indices;
};