#include "MeshComponent.hpp"
#include "../Engine.hpp"

MeshComponent::MeshComponent(size_t id) noexcept : id(id) {}

void MeshComponent::InitializeComponent(Engine* engine)
{
	this->engine = engine;
	mesh = engine->gameDataManager.LoadMesh(id);
}

void MeshComponent::Render()
{
	RenderSubComponents();
	mesh->Draw();
};