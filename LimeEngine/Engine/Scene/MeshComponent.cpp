#include "MeshComponent.hpp"
#include "../Engine.hpp"

namespace LimeEngine
{
	MeshComponent::MeshComponent(Engine* engine, Transform transform, size_t id) noexcept : SceneComponent(engine, transform), id(id)
	{
		mesh = engine->gameDataManager.LoadMesh(id);
		AddToRender();
	}

	void MeshComponent::Render(const CameraComponent* camera)
	{
		if (engine->scene.CameraIsSet())
		{
			mesh->Draw(camera, GetWorldTransformMatrix());
		}
	}
	void MeshComponent::AddToRender()
	{
		engine->window.graphics.drawer.AddToRender(this);
	}
	bool MeshComponent::RemoveFromRender()
	{
		return engine->window.graphics.drawer.RemoveFromRender(this);
	}
}