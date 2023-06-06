#include "lepch.hpp"
#include "MeshComponent.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	MeshComponent::MeshComponent(Engine* engine, const std::string& componentName, const Transform& transform, const ResourcePath& resourcePath) :
		SceneComponent(engine, componentName, transform), mesh(engine->dataLayer.GetGameDataManager().LoadMesh(resourcePath))
	{
		ShowMesh();
	}

	MeshComponent::MeshComponent(Engine* engine, GameResourceRef<Mesh> mesh, const std::string& componentName, const Transform& transform) :
		SceneComponent(engine, componentName, transform), mesh(mesh)
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

	void MeshComponent::Draw(Renderer& renderer)
	{
		renderer.Draw(*mesh.Get(), GetWorldTransformMatrix());
	}

	float MeshComponent::GetDistance(const Vector& target) noexcept
	{
		// TODO: Add distance calculation
		return 0.0f;
	}

	void MeshComponent::DebugUpdate()
	{
		bool visibility = isVisible;
		if (RuntimeEditor::Input(std::format("IsVisible {}", GetComponentName()), visibility))
		{
			SetVisibility(visibility);
		}
		SceneComponent::DebugUpdate();
	}
}