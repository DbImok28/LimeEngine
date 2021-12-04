#pragma once
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
	Mesh* LoadMesh(size_t id);
	Material* LoadMaterial(size_t id);
	Texture2D* LoadTexture2D(size_t id);

public:
	GameData<Mesh> meshes;
	GameData<Material> materials;
	GameData<Texture2D> textures2D;

private:
	Engine* engine;
};