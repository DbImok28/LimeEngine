#pragma once
#include "../../Base/RenderData.hpp"
#include "../../../Base/Vertex.hpp"
#include "RenderingSystemDX11.hpp"
#include "BuffersDX11.hpp"
#include "ConstantBuffers.hpp"

namespace LimeEngine
{
	class MeshRenderDataDX11 : public MeshRenderData
	{
	public:
		MeshRenderDataDX11(RenderingSystemDX11& renderer, const std::vector<Vertex>& vertices, const std::vector<uint>& indices);
		virtual ~MeshRenderDataDX11() override = default;

		void InitializeBuffers(const std::vector<Vertex>& vertices, const std::vector<uint>& indices);
		void ApplyMaterial(Material* material);
		void ApplyTransform(const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix) noexcept;
		void ApplyBuffers() noexcept;
		virtual void BindData(Material* material, const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix) override;

	public:
		RenderingSystemDX11& renderer;
		VertexShaderConstantBufferDX11<VSTransformConstantBuffer> transformConstantBuffer;
		VertexBufferDX11<Vertex> vertexBuffer;
		IndexBufferDX11 indexBuffer;
	};
}