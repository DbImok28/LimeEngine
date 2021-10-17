#pragma once
#include "../Scene/SceneComponent.hpp"

class Map
{
public:
	Map(Engine* engine) noexcept;
	Map(Map&&) noexcept = default;
	Map& operator=(Map&&) noexcept = default;


	virtual void LoadScane() = 0;
	void Update();
	void Render();
public:
	std::unique_ptr<SceneComponent> rootComponent;
	Engine* engine;
	/*
	-1|
	  |-2|-3
	  |  |-4
	  |
	  |-5|-6
	  |  |-7
	  |  |-8|-9
	  |     |-10	  
	*/
};