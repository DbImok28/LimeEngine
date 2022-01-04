#pragma once
#include "SceneObject.hpp"
#include "MeshComponent.hpp"

namespace LimeEngine
{
	class MeshObject : public SceneObject
	{
	public:
		MeshObject(Engine* engine, Transform transform, size_t id = 0) noexcept;
	};
}