// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Scene/Components/SceneComponent.hpp"

namespace LimeEngine
{
	class SceneObject : public SceneComponent
	{
	public:
		explicit SceneObject(Engine* engine, const std::string& objectName = "SceneObject") noexcept;
		virtual ~SceneObject() noexcept = default;

		std::string GetObjectName() const noexcept;
		Transform GetObjectTransform() const noexcept;
	};
}
