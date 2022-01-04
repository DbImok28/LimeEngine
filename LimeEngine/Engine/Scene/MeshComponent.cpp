#include "MeshComponent.hpp"
#include "../Engine.hpp"

namespace LimeEngine
{
	MeshComponent::MeshComponent(Engine* engine, Transform transform, size_t id) noexcept : SceneComponent(engine, transform), id(id)
	{
		mesh = engine->gameDataManager.LoadMesh(id);
	}

	void MeshComponent::Render()
	{
		if (engine->scene.CameraIsSet())
		{
			mesh->Draw(*engine->scene.GetCamera(), GetWorldTransformMatrix());
		}
	};
}