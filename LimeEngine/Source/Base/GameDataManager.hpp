// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "GameDataLoader.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/Material.hpp"
#include "Graphics/Texture2D.hpp"

namespace LimeEngine
{
	class Engine;
	class Mesh;
	class MaterialBase;
	class Texture2D;

	class GameDataManager
	{
	public:
		GameDataManager() = default;

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
			const auto& [pos, isInserted] = resources.emplace(resourcePath, MakeUnique<TResource>(std::forward<TArgs>(args)...));
			LE_CORE_ASSERT(isInserted, "Resource named {} already exists", resourcePath.GetPath());
			return pos->second->GetRef<TResource>();
		}
		template <std::derived_from<GameResource> TResource>
		[[nodiscard]] GameResourceRef<TResource> Register(const ResourcePath& resourcePath, URef<TResource>&& resource)
		{
			const auto& [pos, isInserted] = resources.emplace(resourcePath, std::move(resource));
			LE_CORE_ASSERT(isInserted, "Resource named {} already exists", resourcePath.GetPath());
			return pos->second->GetRef<TResource>();
		}
		[[nodiscard]] GameResourceRef<GameResource> Register(const ResourcePath& resourcePath, URef<GameResource>&& resource)
		{
			return Register<GameResource>(resourcePath, std::move(resource));
		}

		[[nodiscard]] GameResourceRef<Mesh> CreateMesh(const ResourcePath& resourcePath, const std::vector<Vertex>& vertices, const std::vector<uint>& indices)
		{
			return Emplace<Mesh>(resourcePath, resourcePath, vertices, indices);
		}
		[[nodiscard]] GameResourceRef<Mesh> CreateMesh(const ResourcePath& resourcePath, const std::vector<std::pair<std::vector<Vertex>, std::vector<uint>>>& segmentData)
		{
			return Emplace<Mesh>(resourcePath, resourcePath, segmentData);
		}
		[[nodiscard]] GameResourceRef<MaterialAsset> CreateMaterial(
			const ResourcePath& resourcePath, URef<VertexShader>&& vertexShader, URef<PixelShader>&& pixelShader, MaterialParameters&& parameters, MaterialType type)
		{
			return Emplace<MaterialAsset>(resourcePath, resourcePath, std::move(vertexShader), std::move(pixelShader), std::move(parameters), type);
		}
		[[nodiscard]] GameResourceRef<Texture2D> CreateTexture2D(const ResourcePath& resourcePath, const std::wstring& filePath, TextureFormat format, TextureType type)
		{
			return Register(resourcePath, Texture2D::Create(resourcePath, filePath, format, type));
		}

		// Load

		GameResourceRef<Mesh> LoadMesh(const ResourcePath& resourcePath);
		GameResourceRef<MaterialAsset> LoadMaterial(const ResourcePath& resourcePath);
		GameResourceRef<Texture2D> LoadTexture2D(const ResourcePath& resourcePath);

	public:
		const std::map<ResourcePath, URef<GameResource>>& GetAllResources() const noexcept
		{
			return resources;
		}

	private:
		std::map<ResourcePath, URef<GameResource>> resources;
		GameDataLoader loader;
	};
}