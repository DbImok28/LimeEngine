#pragma once
#include "SceneObject.hpp"
#include "MeshComponent.hpp"

namespace LimeEngine
{
	class MeshObject : public SceneObject
	{
	public:
		MeshObject(size_t id) noexcept;
	};
}