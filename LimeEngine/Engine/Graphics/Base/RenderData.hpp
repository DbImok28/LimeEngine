#pragma once
#include "Material.hpp"
#include "../../Scene/CameraComponent.hpp"

namespace LimeEngine
{
	class MeshRenderData
	{
	public:
		virtual ~MeshRenderData() = default;
		virtual void BindData(Material* material, const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix) = 0;
	};
}