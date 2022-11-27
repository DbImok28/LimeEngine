#include "GameDataManager.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	GameDataManager::GameDataManager(Engine* engine, const GraphicFactory* graphicFactory) noexcept : engine(engine), graphicFactory(graphicFactory) {}

	GameResourceRef<Mesh> GameDataManager::LoadMesh(const ResourcePath& resourcePath)
	{
		if (auto res = GetStoredResource<Mesh>(resourcePath); res) return *res;
		return Register<Mesh>(resourcePath, graphicFactory->CreateMesh(LoadResourceData(resourcePath, graphicFactory->GetMeshLoadParams())));
	}

	GameResourceRef<Material> GameDataManager::LoadMaterial(const ResourcePath& resourcePath)
	{
		if (auto res = GetStoredResource<Material>(resourcePath); res) return *res;
		return Register<Material>(resourcePath, graphicFactory->CreateMaterial(LoadResourceData(resourcePath, graphicFactory->GetMaterialLoadParams())));
	}

	GameResourceRef<Texture2D> GameDataManager::LoadTexture2D(const ResourcePath& resourcePath)
	{
		if (auto res = GetStoredResource<Texture2D>(resourcePath); res) return *res;
		return Register<Texture2D>(resourcePath, graphicFactory->CreateTexture2D(LoadResourceData(resourcePath, graphicFactory->GetTexture2DLoadParams())));
	}
}