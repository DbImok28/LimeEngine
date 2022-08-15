#include "RenderDataDX11.hpp"

namespace LimeEngine
{
	MeshRenderDataDX11::MeshRenderDataDX11(RenderingSystemDX11& renderer, const std::vector<Vertex>& vertices, const std::vector<uint>& indices) :
		renderer(renderer), vertexBuffer(renderer), indexBuffer(renderer), transformConstantBuffer(renderer)
	{
		InitializeBuffers(vertices, indices);
	}

	void MeshRenderDataDX11::InitializeBuffers(const std::vector<Vertex>& vertices, const std::vector<uint>& indices)
	{
		auto device = renderer.GetDevice();
		auto deviceContext = renderer.GetDeviceContext();
		GFX_CHECK_HR_MSG(vertexBuffer.Initialize(vertices), "Failed to initialize vertex buffer.");
		GFX_CHECK_HR_MSG(indexBuffer.Initialize(indices), "Failed to initialize index buffer.");
		GFX_CHECK_HR_MSG(transformConstantBuffer.Initialize(), "Failed to initialize constant buffer Coordinates.");
	}

	void MeshRenderDataDX11::ApplyMaterial(Material* material)
	{
		material->ApplyMaterial();
	}

	void MeshRenderDataDX11::ApplyTransform(const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix) noexcept
	{
		transformConstantBuffer.data.wvpMatrix = XMMatrixTranspose(transformMatrix * cameraComponent->GetViewProjectionMatrix());
		transformConstantBuffer.data.worldMatrix = XMMatrixTranspose(transformMatrix);
		transformConstantBuffer.ApplyChanges();
	}

	void MeshRenderDataDX11::ApplyBuffers() noexcept
	{
		indexBuffer.Bind();
		vertexBuffer.Bind();
		transformConstantBuffer.Bind();
	}

	void MeshRenderDataDX11::BindData(Material* material, const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix)
	{
		ApplyBuffers();
		ApplyTransform(cameraComponent, transformMatrix);
		ApplyMaterial(material);
	}
}