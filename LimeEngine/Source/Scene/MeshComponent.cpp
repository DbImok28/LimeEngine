#include "lepch.hpp"
#include "MeshComponent.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	MeshComponent::MeshComponent(Engine* engine, const Transform& transform, const ResourcePath& resourcePath) :
		SceneComponent(engine, transform), mesh(engine->gameDataManager.LoadMesh(resourcePath))
	{
		ShowMesh();
	}

	MeshComponent::MeshComponent(Engine* engine, const Transform& transform, GameResourceRef<Mesh> mesh) : SceneComponent(engine, transform), mesh(mesh)
	{
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
		engine->renderLayer.AddToRender(this);
	}

	void MeshComponent::HideMesh()
	{
		if (!isVisible) return;
		isVisible = false;
		engine->renderLayer.RemoveFromRender(this);
	}

	// Inherited via Drawable

	void MeshComponent::Draw(Renderer& renderer)
	{
		renderer.Draw(*mesh.Get(), GetWorldTransformMatrix());
	}

	float MeshComponent::GetDistance(const Vector& target) noexcept
	{
		// TODO: Add distance calculation
		return 0.0f;
	}
}