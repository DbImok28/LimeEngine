#pragma once
#include "SceneObject.hpp"
#include "Scene/Components/MeshComponent.hpp"

namespace LimeEngine
{
	class MeshObject : public SceneObject
	{
	public:
		explicit MeshObject(
			Engine* engine, const std::string& componentName = "MeshComponent", const Transform& transform = {}, const ResourcePath& meshResourcePath = "Engine\\NullMesh");
		MeshObject(Engine* engine, GameResourceRef<Mesh> mesh, const std::string& componentName = "MeshComponent", const Transform& transform = {});
	};
}