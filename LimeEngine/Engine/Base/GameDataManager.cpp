#include "GameDataManager.hpp"
#include "../Engine.hpp"

namespace LimeEngine
{
	GameDataManager::GameDataManager(Engine* engine, const GraphicFactory* graphicFactory) noexcept : engine(engine), graphicFactory(graphicFactory) {}

	GameResourceRef<Mesh> GameDataManager::LoadMesh(std::string gamePath)
	{
		if (auto res = GetStoredResource<Mesh>(gamePath); res) return *res;
		return Register<Mesh>(gamePath, graphicFactory->CreateMesh(LoadResourceData(gamePath, graphicFactory->GetMeshLoadParams())));
	}

	GameResourceRef<Material> GameDataManager::LoadMaterial(std::string gamePath)
	{
		if (auto res = GetStoredResource<Material>(gamePath); res) return *res;
		return Register<Material>(gamePath, graphicFactory->CreateMaterial(LoadResourceData(gamePath, graphicFactory->GetMaterialLoadParams())));
	}

	GameResourceRef<Texture2D> GameDataManager::LoadTexture2D(std::string gamePath)
	{
		if (auto res = GetStoredResource<Texture2D>(gamePath); res) return *res;
		return Register<Texture2D>(gamePath, graphicFactory->CreateTexture2D(LoadResourceData(gamePath, graphicFactory->GetTexture2DLoadParams())));
	}
}