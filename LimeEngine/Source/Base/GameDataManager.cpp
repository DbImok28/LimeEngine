// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "GameDataManager.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	GameDataManager::GameDataManager(Engine* engine) noexcept : engine(engine) {}

	GameResourceRef<Mesh> GameDataManager::LoadMesh(const ResourcePath& resourcePath)
	{
		if (auto res = GetStoredResource<Mesh>(resourcePath); res) return *res;
		std::string meshLoadParams = "";
		//return Register<Mesh>(resourcePath, Mesh::Create(resourcePath, LoadResourceData(resourcePath, meshLoadParams)));
		return {};
	}

	GameResourceRef<MaterialAsset> GameDataManager::LoadMaterial(const ResourcePath& resourcePath)
	{
		if (auto res = GetStoredResource<MaterialAsset>(resourcePath); res) return *res;
		std::string materialLoadParams = "";
		//return Register<MaterialAsset>(resourcePath, MaterialAsset::Create(resourcePath, LoadResourceData(resourcePath, materialLoadParams)));
		return {};
	}

	GameResourceRef<Texture2D> GameDataManager::LoadTexture2D(const ResourcePath& resourcePath)
	{
		if (auto res = GetStoredResource<Texture2D>(resourcePath); res) return *res;
		std::string texture2DLoadParams = "";
		//return Register<Texture2D>(resourcePath, Texture2D::Create(resourcePath, LoadResourceData(resourcePath, texture2DLoadParams)));
		return {};
	}
}
