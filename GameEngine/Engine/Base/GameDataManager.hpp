#pragma once
#include "Map.hpp"

class Engine;
class GameDataManager
{
	// load game data
public:
	GameDataManager(com_ptr<ID3D11Device> device, com_ptr<ID3D11DeviceContext> deviceContext, Engine* engine);
	void StartupLoading();
	void Update();
	Engine* pEngine;
	Map map;
	com_ptr<ID3D11Device> device;
	com_ptr<ID3D11DeviceContext> deviceContext;
};