#include "lepch.hpp"
#include "MeshObject.hpp"

namespace LimeEngine
{
	MeshObject::MeshObject(Engine* engine, const std::string& componentName, const Transform& transform, const ResourcePath& meshResourcePath) : SceneObject(engine)
	{
		rootComponent = std::make_unique<MeshComponent>(engine, componentName, transform, meshResourcePath);
	}

	MeshObject::MeshObject(Engine* engine, const std::string& componentName, const Transform& transform, GameResourceRef<Mesh> mesh) : SceneObject(engine)
	{
		rootComponent = std::make_unique<MeshComponent>(engine, componentName, transform, mesh);
	}
}