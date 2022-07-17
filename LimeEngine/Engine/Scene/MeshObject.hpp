#pragma once
#include "SceneObject.hpp"
#include "MeshComponent.hpp"

namespace LimeEngine
{
	class MeshObject : public SceneObject
	{
	public:
		explicit MeshObject(Engine* engine, const Transform& transform = {}, size_t id = 0);
	};
}