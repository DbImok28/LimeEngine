// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "RenderDataDX11.hpp"

namespace LimeEngine
{
	MeshRenderDataDX11::MeshRenderDataDX11(RendererDX11& renderer, const std::vector<Vertex>& vertices, const std::vector<uint>& indices) :
		renderer(renderer), vertexBuffer(renderer), indexBuffer(renderer), transformConstantBuffer(renderer)
	{
		InitializeBuffers(vertices, indices);
	}

	void MeshRenderDataDX11::InitializeBuffers(const std::vector<Vertex>& vertices, const std::vector<uint>& indices)
	{
		vertexBuffer.Initialize(vertices);
		indexBuffer.Initialize(indices);
		transformConstantBuffer.Initialize();
	}

	void MeshRenderDataDX11::ApplyMaterial(MaterialInstance* materialInstance)
	{
		materialInstance->ApplyMaterial();
	}

	void MeshRenderDataDX11::ApplyTransform(const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix)
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

	void MeshRenderDataDX11::BindData(MaterialInstance* materialInstance, const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix)
	{
		ApplyBuffers();
		ApplyTransform(cameraComponent, transformMatrix);
		ApplyMaterial(materialInstance);
	}
}