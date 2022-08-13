#include "../Engine.hpp"
#include "GameDataManager.hpp"
#include "../Helpers/Paths.hpp"

namespace LimeEngine
{
	GameDataManager::GameDataManager(Engine* engine) noexcept : engine(engine) {}

	Mesh* GameDataManager::CreateMesh(RenderingSystemDX11& renderer, const std::vector<Vertex>& vertices, const std::vector<uint>& indices)
	{
		return meshes.Create(meshes.GetLastId() + 1, renderer, vertices, indices, meshes.GetLastId() + 1);
	}

	Texture2D* GameDataManager::CreateTexture2D(RenderingSystemDX11& renderer)
	{
		return textures2D.Create(textures2D.GetLastId() + 1, renderer, textures2D.GetLastId() + 1);
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
}