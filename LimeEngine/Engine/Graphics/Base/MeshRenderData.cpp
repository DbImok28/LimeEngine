#include "MeshRenderData.hpp"

namespace LimeEngine
{
	MeshRenderData::MeshRenderData(const RenderingSystemDX11* renderer, const std::vector<Vertex>& vertices, const std::vector<uint>& indices) : renderer(renderer)
	{
		InitializeBuffers(vertices, indices);
	}

	void MeshRenderData::InitializeBuffers(const std::vector<Vertex>& vertices, const std::vector<uint>& indices)
	{
		auto device = renderer->device.Get();
		auto deviceContext = renderer->deviceContext.Get();
		GFX_CHECK_HR_MSG(vertexBuffer.Initialize(device, deviceContext, vertices.data(), static_cast<UINT>(vertices.size())), "Failed to initialize vertex buffer.");
		GFX_CHECK_HR_MSG(indexBuffer.Initialize(device, deviceContext, indices.data(), static_cast<UINT>(indices.size())), "Failed to initialize index buffer.");
		GFX_CHECK_HR_MSG(cbCoordinates.Initialize(device, deviceContext), "Failed to initialize constant buffer Coordinates.");
	}

	void MeshRenderData::ApplyMaterial(Material* material)
	{
		material->ApplyConstantBuffer(renderer, cbCoordinates);
		material->ApplyMaterial(renderer);
	}

	void MeshRenderData::ApplyTransform(const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix) noexcept
	{
		cbCoordinates.data.wvpMatrix = XMMatrixTranspose(transformMatrix * cameraComponent->GetViewProjectionMatrix());
		cbCoordinates.data.worldMatrix = XMMatrixTranspose(transformMatrix);
	}

	void MeshRenderData::ApplyBuffers() const noexcept
	{
		indexBuffer.Bind();
		vertexBuffer.Bind();
	}

	void MeshRenderData::ApplyTransformAndMaterial(Material* material, const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix)
	{
		ApplyTransform(cameraComponent, transformMatrix);
		ApplyMaterial(material);
	}
}