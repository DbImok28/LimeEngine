// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Graphics/RenderData.hpp"
#include "Base/Vertex.hpp"
#include "RendererDX11.hpp"
#include "BuffersDX11.hpp"
#include "ConstantBuffers.hpp"

namespace LimeEngine
{
	class MeshRenderDataDX11 : public MeshRenderData
	{
	public:
		MeshRenderDataDX11(RendererDX11& renderer, const std::vector<Vertex>& vertices, const std::vector<uint>& indices);
		virtual ~MeshRenderDataDX11() override = default;

		void InitializeBuffers(const std::vector<Vertex>& vertices, const std::vector<uint>& indices);
		void ApplyMaterial(MaterialInstance* materialInstance);
		void ApplyTransform(const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix);
		void ApplyBuffers() noexcept;
		virtual void BindData(MaterialInstance* materialInstance, const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix) override;

	public:
		RendererDX11& renderer;
		VertexBufferDX11<Vertex> vertexBuffer;
		IndexBufferDX11 indexBuffer;
		VertexShaderConstantBufferDX11<VSTransformConstantBuffer> transformConstantBuffer;
	};
}