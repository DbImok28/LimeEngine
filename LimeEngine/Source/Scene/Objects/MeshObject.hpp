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
		MeshObject(Engine* engine, const std::string& componentName, const Transform& transform, GameResourceRef<Mesh> mesh);
	};
}