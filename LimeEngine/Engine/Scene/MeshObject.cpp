#include "MeshObject.hpp"

MeshObject::MeshObject(size_t id) noexcept
{
	components.push_back(std::make_unique<MeshComponent>(id));
}
