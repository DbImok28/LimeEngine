#pragma once
#include <vector>
#include <memory>
//#include "../Engine.hpp"

class Engine;

class SceneComponent
{
public:
	SceneComponent() noexcept = default;
	virtual void InitializeComponent(Engine* engine);
	virtual void Update(/*...*/);
	virtual void Render();
	virtual ~SceneComponent() noexcept;
	
	void AttachComponent(std::unique_ptr<SceneComponent>&& component) noexcept;
	void RenderSubComponents();
	void UpdateSubComponents();
public:
	Engine* engine = nullptr;
	std::vector<std::unique_ptr<SceneComponent>> subComponents;
};