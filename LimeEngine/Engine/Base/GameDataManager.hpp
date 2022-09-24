#pragma once
#include "GameDataLoader.hpp"
#include "../Graphics/Base/GraphicFactory.hpp"
#include <map>
#include <optional>
#include <memory>
#include <concepts>

#include "../Graphics/Base/Mesh.hpp"
#include "../Graphics/Base/Material.hpp"
#include "../Graphics/Base/Texture2D.hpp"

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

		GameResourceData LoadResourceData(const std::string& gamePath, const std::string& loadParams) const
		{
			return loader.LoadResource(gamePath, loadParams);
		}

		std::optional<GameResourceRef<GameResource>> GetStoredResource(const std::string& gamePath) const noexcept
		{
			if (auto it = resources.find(gamePath); it != resources.end()) return it->second->GetRef<GameResource>();
			return {};
		}
		template <std::derived_from<GameResource> TResource>
		std::optional<GameResourceRef<TResource>> GetStoredResource(const std::string& gamePath) const noexcept
		{
			if (auto it = resources.find(gamePath); it != resources.end()) return it->second->GetRef<TResource>();
			return {};
		}
		void Release()
		{
			// TODO: Call Release
			std::erase_if(resources, [](const auto& item) { return item.second->RefCount() <= 0; });
		}

		template <std::derived_from<GameResource> TResource, typename... TArgs>
		[[nodiscard]] GameResourceRef<TResource> Emplace(const std::string& gamePath, TArgs&&... args)
		{
			// TODO:Add gamePath validation
			return resources.emplace(gamePath, std::make_unique<TResource>(std::forward<TArgs>(args)...)).first->second->GetRef<TResource>();
		}
		[[nodiscard]] GameResourceRef<GameResource> Register(std::string& gamePath, std::unique_ptr<GameResource>&& resource)
		{
			return resources.emplace(gamePath, std::move(resource)).first->second->GetRef<GameResource>();
		}
		template <std::derived_from<GameResource> TResource>
		[[nodiscard]] GameResourceRef<TResource> Register(const std::string& gamePath, std::unique_ptr<TResource>&& resource)
		{
			return resources.emplace(gamePath, std::move(resource)).first->second->GetRef<TResource>();
		}

		[[nodiscard]] GameResourceRef<Mesh> CreateMesh(const std::string& gamePath, const std::vector<Vertex>& vertices, const std::vector<uint>& indices)
		{
			return Emplace<Mesh>(gamePath, gamePath, graphicFactory, vertices, indices);
		}
		[[nodiscard]] GameResourceRef<MasterMaterial> CreateMasterMaterial(const std::string& gamePath, IBindable* vertexShader, IBindable* pixelShader, MaterialType type)
		{
			return Emplace<MasterMaterial>(gamePath, gamePath, vertexShader, pixelShader, type);
		}
		[[nodiscard]] GameResourceRef<Texture2D> CreateTexture2D(const std::string& gamePath, const std::wstring& filePath, TextureType type)
		{
			return Register(gamePath, graphicFactory->CreateTexture2D(gamePath, filePath, type));
		}

		// Load

		GameResourceRef<Mesh> LoadMesh(const std::string& gamePath);
		GameResourceRef<Material> LoadMaterial(const std::string& gamePath);
		GameResourceRef<Texture2D> LoadTexture2D(const std::string& gamePath);

	private:
		std::map<std::string, std::unique_ptr<GameResource>> resources;
		const GraphicFactory* graphicFactory;
		Engine* engine;
		GameDataLoader loader;
	};
}