#include "SceneComponent.hpp"

void SceneComponent::InitializeComponent(Engine* engine)
{
	this->engine = engine;
	for (auto&& component : subComponents)
	{
		component->InitializeComponent(engine);
	}
}

void SceneComponent::Update()
{
	UpdateSubComponents();
}

void SceneComponent::Render()
{
	RenderSubComponents();
}

SceneComponent::~SceneComponent() noexcept
{
}

void SceneComponent::AttachComponent(std::unique_ptr<SceneComponent>&& component) noexcept
{
	subComponents.push_back(std::move(component));
}
	
void SceneComponent::RenderSubComponents()
{
	for (auto&& component : subComponents)
	{
		component->Render();
	}
}

void SceneComponent::UpdateSubComponents()
{
	for (auto&& component : subComponents)
	{
		component->Update();
	}
}