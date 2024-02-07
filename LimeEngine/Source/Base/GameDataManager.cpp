// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "GameDataManager.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	GameDataManager::GameDataManager(Engine* engine, const GraphicFactory* graphicFactory) noexcept : engine(engine), graphicFactory(graphicFactory) {}

	GameResourceRef<Mesh> GameDataManager::LoadMesh(const ResourcePath& resourcePath)
	{
		if (auto res = GetStoredResource<Mesh>(resourcePath); res) return *res;
		return Register<Mesh>(resourcePath, graphicFactory->CreateMesh(resourcePath, LoadResourceData(resourcePath, graphicFactory->GetMeshLoadParams())));
	}

	GameResourceRef<MaterialBase> GameDataManager::LoadMaterial(const ResourcePath& resourcePath)
	{
		if (auto res = GetStoredResource<MaterialBase>(resourcePath); res) return *res;
		return Register<MaterialBase>(resourcePath, graphicFactory->CreateMaterial(resourcePath, LoadResourceData(resourcePath, graphicFactory->GetMaterialLoadParams())));
	}

	GameResourceRef<Texture2D> GameDataManager::LoadTexture2D(const ResourcePath& resourcePath)
	{
		if (auto res = GetStoredResource<Texture2D>(resourcePath); res) return *res;
		return Register<Texture2D>(resourcePath, graphicFactory->CreateTexture2D(resourcePath, LoadResourceData(resourcePath, graphicFactory->GetTexture2DLoadParams())));
	}
}
