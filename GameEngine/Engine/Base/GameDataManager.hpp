#pragma once
#include "../Graphics/Graphics.hpp"
#include "Map.hpp"

class Engine;
class GameDataManager
{
	// load game data
public:
	GameDataManager(Graphics* gfx) noexcept;
	void StartupLoading();
	void Update();
	Map map;

	Graphics* graphics;
};