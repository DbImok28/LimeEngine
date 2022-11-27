#pragma once
#include "SceneObject.hpp"
#include "MeshComponent.hpp"

namespace LimeEngine
{
	class MeshObject : public SceneObject
	{
	public:
		explicit MeshObject(Engine* engine, const Transform& transform = {}, std::string path = "Engine\\NullMesh");
		MeshObject(Engine* engine, const Transform& transform, GameResourceRef<Mesh> mesh);
	};
}