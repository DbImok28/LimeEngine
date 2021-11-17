#include "MeshComponent.hpp"
#include "../Engine.hpp"

MeshComponent::MeshComponent(size_t id) noexcept : id(id) {}

void MeshComponent::Initialize(Engine* engine)
{
	this->engine = engine;
	mesh = engine->gameDataManager.LoadMesh(id);
}

void MeshComponent::Render()
{
	mesh->Draw();
};