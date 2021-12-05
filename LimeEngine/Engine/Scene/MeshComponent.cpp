#include "MeshComponent.hpp"
#include "../Engine.hpp"

namespace LimeEngine
{
	MeshComponent::MeshComponent(size_t id) noexcept : id(id) {}

	void MeshComponent::Initialize(Engine* engine, SceneObject* rootObject)
	{
		this->engine = engine;
		this->rootObject = rootObject;
		mesh = engine->gameDataManager.LoadMesh(id);
	}

	void MeshComponent::Render()
	{
		mesh->Draw(*engine->window.graphics.camera.get(), GetWorldTransformMatrix());
	};
}