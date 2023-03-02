#include "lepch.hpp"
#include "MeshObject.hpp"

namespace LimeEngine
{
	MeshObject::MeshObject(Engine* engine, const Transform& transform, const ResourcePath& meshResourcePath) : SceneObject(engine)
	{
		rootComponent = std::make_unique<MeshComponent>(engine, transform, meshResourcePath);
	}

	MeshObject::MeshObject(Engine* engine, const Transform& transform, GameResourceRef<Mesh> mesh) : SceneObject(engine)
	{
		rootComponent = std::make_unique<MeshComponent>(engine, transform, mesh);
	}
}