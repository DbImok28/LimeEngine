#include "MeshDX11.hpp"
#include "../../Base/Mesh.hpp"
#include "../../../Scene/MeshComponent.hpp"
#include "../../../Exceptions/GraphicsExceptions.hpp"

namespace LimeEngine
{
	MeshDX11::MeshDX11(const RenderingSystemDX11& renderer, Mesh* mesh) : renderer(renderer), mesh(mesh)
	{
		InitializeBuffers();
	}

	void MeshDX11::InitializeBuffers()
	{
		auto device = renderer.device.Get();
		auto deviceContext = renderer.deviceContext.Get();
		HRESULT hr;
		GFX_ERROR_IF_MSG(vertexBuffer.Initialize(device, mesh->GetVertices().data(), static_cast<UINT>(mesh->GetVertices().size())), "Failed to initialize vertex buffer.");
		GFX_ERROR_IF_MSG(indexBuffer.Initialize(device, mesh->GetIndices().data(), static_cast<UINT>(mesh->GetIndices().size())), "Failed to initialize index buffer.");
		GFX_ERROR_IF_MSG(cbCoordinates.Initialize(device, deviceContext), "Failed to initialize constant buffer Coordinates.");
	}

	void MeshDX11::ApplyMaterial()
	{
		auto renderMaterial = mesh->GetMaterial()->renderMaterial;
		renderMaterial.ApplyConstantBuffer(cbCoordinates);
		renderMaterial.ApplyMaterial();
	}

	void MeshDX11::UpdateCB(const CameraComponent* cameraComponent, const TempTransformMatrix worldMatrix) noexcept
	{
		cbCoordinates.data.wvpMatrix = XMMatrixTranspose(worldMatrix * cameraComponent->GetViewProjectionMatrix());
		cbCoordinates.data.worldMatrix = XMMatrixTranspose(worldMatrix);
	}

	void MeshDX11::Draw(const CameraComponent* cameraComponent, const TempTransformMatrix worldMatrix)
	{
		UpdateCB(cameraComponent, worldMatrix);
		ApplyMaterial();

		auto deviceContext = renderer.deviceContext.Get();
		UINT offset = 0;
		deviceContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
		deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), vertexBuffer.StridePtr(), &offset);
		deviceContext->DrawIndexed(indexBuffer.Count(), 0, 0);
	}
}