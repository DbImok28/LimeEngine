#include "MeshComponent.hpp"
#include "../Engine.hpp"

namespace LimeEngine
{
	MeshComponent::MeshComponent(size_t id) noexcept : id(id) {}

	void MeshComponent::Initialize(Engine* engine, Transformable* rootTransform)
	{
		this->engine = engine;
		this->rootTransform = rootTransform;
		mesh = engine->gameDataManager.LoadMesh(id);
	}

	void MeshComponent::Render()
	{
		mesh->Draw(*engine->window.graphics.camera.get(), GetWorldTransformMatrix());
		RenderComponents();
	};
}