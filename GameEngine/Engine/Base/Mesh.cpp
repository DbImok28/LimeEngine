#include "Mesh.hpp"
#include "../Exceptions/GraphicsExceptions.hpp"

/*Mesh::Mesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const std::vector<Vertex>& vertices, const std::vector<DWORD>& indices, Material& material, const XMMATRIX& trasformMatrix)
	: deviceContext(deviceContext),
	trasformMatrix(trasformMatrix),
	vertices(vertices),
	indices(indices),
	material(&material)
{
	InitializeBuffers(device);
}

Mesh::Mesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::vector<Vertex>&& vertices, std::vector<DWORD>&& indices, Material& material, const XMMATRIX& trasformMatrix)
	: deviceContext(deviceContext),
	trasformMatrix(trasformMatrix),
	vertices(std::move(vertices)),
	indices(std::move(indices)),
	material(&material)
{
	InitializeBuffers(device);
}*/

Mesh::Mesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const std::vector<Vertex>& vertices, const std::vector<DWORD>& indices, const XMMATRIX& trasformMatrix) : 
	deviceContext(deviceContext),
	vertices(vertices),
	indices(indices),
	trasformMatrix(trasformMatrix)
{
	InitializeBuffers(device);
}

void Mesh::SetMaterial(Material& material) noexcept
{
	this->material = &material;
}

void Mesh::SetMaterial(Material* material) noexcept
{
	this->material = material;
}

void Mesh::InitializeBuffers(ID3D11Device* device)
{
	HRESULT hr;
	GFX_ERROR_IF_MSG(
		vertexBuffer.Initialize(device, this->vertices.data(), static_cast<UINT>(vertices.size())),
		L"Failed to initialize vertex buffer."
	);

	GFX_ERROR_IF_MSG(
		indexBuffer.Initialize(device, this->indices.data(), static_cast<UINT>(indices.size())),
		L"Failed to initialize index buffer."
	);
}

const XMMATRIX& Mesh::GetTransformMatrix() const noexcept
{
	return trasformMatrix;
}

void Mesh::Draw()
{
	material->Apply();
	UINT offset = 0;
	deviceContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), vertexBuffer.StridePtr(), &offset);
	deviceContext->DrawIndexed(indexBuffer.Count(), 0, 0);
}