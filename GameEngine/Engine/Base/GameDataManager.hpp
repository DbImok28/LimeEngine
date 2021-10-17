#pragma once
#include "Map.hpp"

#include "Mesh.hpp"
#include "Material.hpp"
#include "Texture2D.hpp"
#include "GameData.hpp"

class Engine;

class GameDataManager
{
	// load game data
public:
	GameDataManager(Engine* engine) noexcept;
	void StartupLoading();
	void Update() noexcept;
	void Render() noexcept;

	Mesh* LoadMesh(size_t id);

	Material* LoadMaterial(size_t id);

	Texture2D* LoadTexture2D(size_t id);

	GameData<Mesh> meshes;
	GameData<Material> materials;
	GameData<Texture2D> textures2D;
	std::vector<std::unique_ptr<Map>> maps; // TODO: Remove
private:
	Engine* engine;
};