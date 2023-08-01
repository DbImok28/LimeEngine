// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "GameDataLoader.hpp"
#include "Graphics/GraphicFactory.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/Material.hpp"
#include "Graphics/Texture2D.hpp"

namespace LimeEngine
{
	class Engine;
	class Mesh;
	class Material;
	class Texture2D;

	class GameDataManager
	{
	public:
		GameDataManager(Engine* engine, const GraphicFactory* graphicFactory) noexcept;

		GameResourceData LoadResourceData(const ResourcePath& resourcePath, const std::string& loadParams) const
		{
			return loader.LoadResource(resourcePath, loadParams);
		}

		std::optional<GameResourceRef<GameResource>> GetStoredResource(const ResourcePath& resourcePath) const noexcept
		{
			if (auto it = resources.find(resourcePath); it != resources.end()) return it->second->GetRef<GameResource>();
			return {};
		}
		template <std::derived_from<GameResource> TResource>
		std::optional<GameResourceRef<TResource>> GetStoredResource(const ResourcePath& resourcePath) const noexcept
		{
			if (auto it = resources.find(resourcePath); it != resources.end()) return it->second->GetRef<TResource>();
			return {};
		}
		void Release()
		{
			std::erase_if(resources, [](const auto& item) { return item.second->RefCount() <= 0; });
		}
		void Update()
		{
			Release();
		}

		template <std::derived_from<GameResource> TResource, typename... TArgs>
		[[nodiscard]] GameResourceRef<TResource> Emplace(const ResourcePath& resourcePath, TArgs&&... args)
		{
			return resources.emplace(resourcePath, std::make_unique<TResource>(std::forward<TArgs>(args)...)).first->second->GetRef<TResource>();
		}
		[[nodiscard]] GameResourceRef<GameResource> Register(const ResourcePath& resourcePath, std::unique_ptr<GameResource>&& resource)
		{
			return resources.emplace(resourcePath, std::move(resource)).first->second->GetRef<GameResource>();
		}
		template <std::derived_from<GameResource> TResource>
		[[nodiscard]] GameResourceRef<TResource> Register(const ResourcePath& resourcePath, std::unique_ptr<TResource>&& resource)
		{
			return resources.emplace(resourcePath, std::move(resource)).first->second->GetRef<TResource>();
		}

		[[nodiscard]] GameResourceRef<Mesh> CreateMesh(const ResourcePath& resourcePath, const std::vector<Vertex>& vertices, const std::vector<uint>& indices)
		{
			return Emplace<Mesh>(resourcePath, resourcePath, graphicFactory, vertices, indices);
		}
		[[nodiscard]] GameResourceRef<Mesh> CreateMesh(const ResourcePath& resourcePath, const std::vector<std::pair<std::vector<Vertex>, std::vector<uint>>>& segmentData)
		{
			return Emplace<Mesh>(resourcePath, resourcePath, graphicFactory, segmentData);
		}
		[[nodiscard]] GameResourceRef<MasterMaterial> CreateMasterMaterial(const ResourcePath& resourcePath, IBindable* vertexShader, IBindable* pixelShader, MaterialType type)
		{
			return Emplace<MasterMaterial>(resourcePath, resourcePath, vertexShader, pixelShader, type);
		}
		[[nodiscard]] GameResourceRef<Texture2D> CreateTexture2D(const ResourcePath& resourcePath, const std::wstring& filePath, TextureType type)
		{
			return Register(resourcePath, graphicFactory->CreateTexture2D(resourcePath, filePath, type));
		}

		// Load

		GameResourceRef<Mesh> LoadMesh(const ResourcePath& resourcePath);
		GameResourceRef<Material> LoadMaterial(const ResourcePath& resourcePath);
		GameResourceRef<Texture2D> LoadTexture2D(const ResourcePath& resourcePath);

	private:
		std::map<ResourcePath, std::unique_ptr<GameResource>> resources;
		const GraphicFactory* graphicFactory;
		Engine* engine;
		GameDataLoader loader;
	};
}