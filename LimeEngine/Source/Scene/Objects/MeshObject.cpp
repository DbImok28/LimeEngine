#include "lepch.hpp"
#include "MeshObject.hpp"

namespace LimeEngine
{
	MeshObject::MeshObject(Engine* engine, const std::string& objectName, const Transform& transform, const ResourcePath& meshResourcePath) :
		SceneObject(engine, objectName, transform)
	{
		SetupAttachment<MeshComponent>(engine, "MeshComponent", Transform{}, meshResourcePath);
	}

	MeshObject::MeshObject(Engine* engine, GameResourceRef<Mesh> mesh, const std::string& objectName, const Transform& transform) : SceneObject(engine, objectName, transform)
	{
		SetupAttachment<MeshComponent>(engine, mesh);
	}
}
