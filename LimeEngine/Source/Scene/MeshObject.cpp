#include "lepch.hpp"
#include "MeshObject.hpp"

namespace LimeEngine
{
	MeshObject::MeshObject(Engine* engine, const Transform& transform, std::string path) : SceneObject(engine)
	{
		rootComponent = std::make_unique<MeshComponent>(engine, transform, path);
	}

	MeshObject::MeshObject(Engine* engine, const Transform& transform, GameResourceRef<Mesh> mesh) : SceneObject(engine)
	{
		rootComponent = std::make_unique<MeshComponent>(engine, transform, mesh);
	}
}