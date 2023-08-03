// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Material.hpp"
#include "Scene/Components/CameraComponent.hpp"

namespace LimeEngine
{
	class MeshRenderData
	{
	public:
		virtual ~MeshRenderData() = default;
		virtual void BindData(MaterialInstance* materialInstance, const CameraComponent* cameraComponent, const TempTransformMatrix& transformMatrix) = 0;
	};
}