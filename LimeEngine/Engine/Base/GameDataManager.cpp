#include "../Engine.hpp"
#include "GameDataManager.hpp"
#include "../Helpers/Paths.hpp"

namespace LimeEngine
{
	GameDataManager::GameDataManager(Engine* engine) noexcept :
		engine(engine)
	{
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