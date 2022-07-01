#include "MeshObject.hpp"

namespace LimeEngine
{
	MeshObject::MeshObject(Engine* engine, const Transform& transform, size_t id) noexcept : SceneObject(engine)
	{
		rootComponent = std::make_unique<MeshComponent>(engine, transform, id);
	}
}