// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "RenderData.hpp"

namespace LimeEngine
{
	MeshRenderData::MeshRenderData(MeshRenderData&& other) noexcept :
		vertexBuffer(std::move(other.vertexBuffer)), indexBuffer(std::move(other.indexBuffer)), transformConstantBuffer(std::move(other.transformConstantBuffer))
	{
		other.vertexBuffer = nullptr;
		other.indexBuffer = nullptr;
	}

	MeshRenderData& MeshRenderData::operator=(MeshRenderData&& other) noexcept
	{
		if (this != &other)
		{
			vertexBuffer = std::move(other.vertexBuffer);
			indexBuffer = std::move(other.indexBuffer);
			transformConstantBuffer = std::move(other.transformConstantBuffer);
		}

		return *this;
	}

	void MeshRenderData::ApplyMaterial(Material* material)
	{
		material->ApplyMaterial();
	}

	void MeshRenderData::ApplyTransform(const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix)
	{
		transformConstantBuffer.data.wvpMatrix = XMMatrixTranspose(transformMatrix * cameraComponent->GetViewProjectionMatrix());
		transformConstantBuffer.data.worldMatrix = XMMatrixTranspose(transformMatrix);
		transformConstantBuffer.ApplyChanges();
	}

	void MeshRenderData::ApplyBuffers() noexcept
	{
		indexBuffer->Bind();
		vertexBuffer->Bind();
		transformConstantBuffer.Bind();
	}

	void MeshRenderData::BindData(Material* materialInstance, const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix)
	{
		ApplyBuffers();
		ApplyTransform(cameraComponent, transformMatrix);
		ApplyMaterial(materialInstance);
	}
}