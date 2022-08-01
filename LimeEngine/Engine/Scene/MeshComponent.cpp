#include "MeshComponent.hpp"
#include "../Engine.hpp"

namespace LimeEngine
{
	MeshComponent::MeshComponent(Engine* engine, const Transform& transform, size_t id) : SceneComponent(engine, transform)
	{
		mesh = engine->gameDataManager.LoadMesh(id);
		ShowMesh();
	}

	MeshComponent::~MeshComponent()
	{
		HideMesh();
	}

	void MeshComponent::SetVisibility(bool visibility)
	{
		if (isVisible == visibility) return;
		if (visibility)
		{
			ShowMesh();
		}
		else
		{
			HideMesh();
		}
	}

	void MeshComponent::ShowMesh()
	{
		if (isVisible) return;
		isVisible = true;
		engine->AddToRender(this);
	}

	void MeshComponent::HideMesh()
	{
		if (!isVisible) return;
		isVisible = false;
		engine->RemoveFromRender(this);
	}

	// Inherited via Drawable

	void MeshComponent::Draw(RenderingSystem& renderingSystem)
	{
		renderingSystem.Draw(*mesh, GetWorldTransformMatrix());
	}

	float MeshComponent::GetDistance(const Vector& target) noexcept
	{
		// TODO: Add distance calculation
		return 0.0f;
	}
}