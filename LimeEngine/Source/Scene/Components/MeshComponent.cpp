// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "MeshComponent.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	MeshComponent::MeshComponent(Engine* engine, const std::string& componentName) : SceneComponent(engine, componentName), mesh(GameResourceRef<Mesh>::NullRef())
	{
		ShowMesh();
	}

	MeshComponent::~MeshComponent()
	{
		HideMesh();
	}

	void MeshComponent::SetMesh(const ResourcePath& resourcePath)
	{
		mesh = engine->dataLayer.GetGameDataManager().LoadMesh(resourcePath);
	}

	void MeshComponent::SetMesh(GameResourceRef<Mesh> mesh)
	{
		this->mesh = mesh;
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