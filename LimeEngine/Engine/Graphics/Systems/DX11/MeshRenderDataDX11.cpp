#include "MeshRenderDataDX11.hpp"
#include "../../Base/Mesh.hpp"
#include "../../../Exceptions/GraphicsExceptions.hpp"

namespace LimeEngine
{
	MeshRenderDataDX11::MeshRenderDataDX11(ID3D11Device* device, ID3D11DeviceContext* deviceContext, MeshComponent* meshComponent) : 
		device(device), deviceContext(deviceContext), meshComponent(meshComponent)
	{
		InitializeBuffers();
	}

	void MeshRenderDataDX11::InitializeBuffers()
	{
		HRESULT hr;
		Mesh* mesh = meshComponent->mesh;
		GFX_ERROR_IF_MSG(
			vertexBuffer.Initialize(device, mesh->GetVertices().data(), static_cast<UINT>(mesh->GetVertices().size())),
			L"Failed to initialize vertex buffer."
		);
		GFX_ERROR_IF_MSG(
			indexBuffer.Initialize(device, mesh->GetIndices().data(), static_cast<UINT>(mesh->GetIndices().size())),
			L"Failed to initialize index buffer."
		);
		GFX_ERROR_IF_MSG(
			cbCoordinates.Initialize(device, deviceContext),
			L"Failed to initialize constant buffer Coordinates."
		);
	}

	void MeshRenderDataDX11::ApplyMaterial()
	{
		Material* material = meshComponent->mesh->GetMaterial();
		material->ApplyConstantBuffer(cbCoordinates);
		material->Apply();
	}

	void MeshRenderDataDX11::UpdateCB(const CameraComponent* cameraComponent) noexcept
	{
		TempTransformMatrix worldMatrix = meshComponent->GetWorldTransformMatrix();
		cbCoordinates.data.wvpMatrix = XMMatrixTranspose(worldMatrix * cameraComponent->GetViewProjectionMatrix());
		cbCoordinates.data.worldMatrix = XMMatrixTranspose(worldMatrix);
	}

	void MeshRenderDataDX11::Draw(const CameraComponent* cameraComponent)
	{
		UpdateCB(cameraComponent);
		ApplyMaterial();

		UINT offset = 0;
		deviceContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
		deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), vertexBuffer.StridePtr(), &offset);
		deviceContext->DrawIndexed(indexBuffer.Count(), 0, 0);
	}
}