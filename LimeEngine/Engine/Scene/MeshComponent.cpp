#include "MeshComponent.hpp"
#include "../Engine.hpp"

namespace LimeEngine
{
	MeshComponent::MeshComponent(Engine* engine, Transform transform, size_t id) noexcept : SceneComponent(engine, transform)
	{
		mesh = engine->gameDataManager.LoadMesh(id);
		AddToRender();
	}
	void MeshComponent::AddToRender()
	{
		engine->AddToRender(this);
	}
	bool MeshComponent::RemoveFromRender()
	{
		return engine->RemoveFromRender(this);
	}
}