#include "MeshDX11.hpp"
#include "RenderingSystemDX11.hpp"
#include "../../Base/Mesh.hpp"
#include "../../../Scene/MeshComponent.hpp"
#include "../../../Exceptions/GraphicsExceptions.hpp"

namespace LimeEngine
{
	MeshDX11::MeshDX11(const RenderingSystemDX11& renderer, const MeshComponent* mesh) : renderer(renderer), meshComponents{ mesh }
	{
		InitializeBuffers();
	}

	void MeshDX11::AddMeshComponent(const MeshComponent* meshComponent)
	{
		meshComponents.push_back(meshComponent);
	}

	void MeshDX11::RemoveMeshComponent(const MeshComponent* meshComponent) noexcept
	{
		meshComponents.erase(std::find(std::begin(meshComponents), std::end(meshComponents), meshComponent));
	}

	bool MeshDX11::Empty() const noexcept
	{
		return meshComponents.empty();
	}

	void MeshDX11::InitializeBuffers()
	{
		auto device = renderer.device.Get();
		auto deviceContext = renderer.deviceContext.Get();
		auto mesh = meshComponents[0]->mesh;
		HRESULT hr;
		GFX_ERROR_IF_MSG(vertexBuffer.Initialize(device, mesh->GetVertices().data(), static_cast<UINT>(mesh->GetVertices().size())), "Failed to initialize vertex buffer.");
		GFX_ERROR_IF_MSG(indexBuffer.Initialize(device, mesh->GetIndices().data(), static_cast<UINT>(mesh->GetIndices().size())), "Failed to initialize index buffer.");
		GFX_ERROR_IF_MSG(cbCoordinates.Initialize(device, deviceContext), "Failed to initialize constant buffer Coordinates.");
	}

	void MeshDX11::ApplyMaterial(const MeshComponent* component)
	{
		Material* material;
		if (component->material != nullptr)
			material = component->material;
		else
			material = component->mesh->GetMaterial();

		if (material != nullptr)
		{
			// TODO: Material should not store renderMaterial
			auto renderMaterial = material->renderMaterial;
			renderMaterial.ApplyConstantBuffer(cbCoordinates);
			renderMaterial.ApplyMaterial();
		}
	}

	void MeshDX11::ApplyTransform(const CameraComponent* cameraComponent, const MeshComponent* meshComponent) noexcept
	{
		auto worldMatrix = meshComponent->GetTransform().GetTransformMatrix();
		cbCoordinates.data.wvpMatrix = XMMatrixTranspose(worldMatrix * cameraComponent->GetViewProjectionMatrix());
		cbCoordinates.data.worldMatrix = XMMatrixTranspose(worldMatrix);
	}

	void MeshDX11::Render(const CameraComponent* cameraComponent)
	{
		auto deviceContext = renderer.deviceContext.Get();
		UINT offset = 0;
		deviceContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
		deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), vertexBuffer.StridePtr(), &offset);
		for (auto& meshComponent : meshComponents)
		{
			ApplyTransform(cameraComponent, meshComponent);
			ApplyMaterial(meshComponent);
			deviceContext->DrawIndexed(indexBuffer.Count(), 0, 0);
		}
	}
}