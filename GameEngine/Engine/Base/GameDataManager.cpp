#include "../Engine.hpp"
#include "GameDataManager.hpp"
#include "../Helpers/Paths.hpp"

#include "../Maps/TestMap.hpp"
#include "Map.hpp"

GameDataManager::GameDataManager(Engine* engine) noexcept :
	engine(engine)
{
}

void GameDataManager::StartupLoading()
{
	maps.push_back(std::make_unique<TestMap>(engine));
	maps[0]->LoadScane();
}

void GameDataManager::Update() noexcept
{
	for (auto&& map : maps)
	{
		map->Update();
	}
}

void GameDataManager::Render() noexcept
{
	for (auto&& map : maps)
	{
		map->Render();
	}
}

Mesh* GameDataManager::LoadMesh(size_t id)
{
	return meshes.Get(id);
}

Material* GameDataManager::LoadMaterial(size_t id)
{
	return materials.Get(id);
}

Texture2D* GameDataManager::LoadTexture2D(size_t id)
{
	return textures2D.Get(id);
}
