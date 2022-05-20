#include "Mesh.hpp"
#include "../Exceptions/GraphicsExceptions.hpp"

namespace LimeEngine
{
	Mesh::Mesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const std::vector<Vertex>& vertices, const std::vector<DWORD>& indices) :
		deviceContext(deviceContext),
		vertices(vertices),
		indices(indices)
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

	Material* Mesh::GetMaterial() const noexcept
	{
		return material;
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
		GFX_ERROR_IF_MSG(
			cbCoordinates.Initialize(device, deviceContext),
			L"Failed to initialize constant buffer Coordinates."
		);
	}

	void Mesh::Draw(const CameraComponent* camera, TempTransformMatrix worldMatrix)
	{
		cbCoordinates.data.wvpMatrix = XMMatrixTranspose(worldMatrix * camera->GetViewProjectionMatrix());
		cbCoordinates.data.worldMatrix = XMMatrixTranspose(worldMatrix);
		GetMaterial()->ApplyConstantBuffer(cbCoordinates);
		material->Apply();
		UINT offset = 0;
		deviceContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
		deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), vertexBuffer.StridePtr(), &offset);
		deviceContext->DrawIndexed(indexBuffer.Count(), 0, 0);
	}
}