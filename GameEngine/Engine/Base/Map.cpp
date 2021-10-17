#include "Map.hpp"

Map::Map(Engine* engine) noexcept : engine(engine), rootComponent(std::make_unique<SceneComponent>())
{
	rootComponent->InitializeComponent(engine);
}

void Map::Update()
{
	rootComponent->Update();
}

void Map::Render()
{
	rootComponent->Render();
}