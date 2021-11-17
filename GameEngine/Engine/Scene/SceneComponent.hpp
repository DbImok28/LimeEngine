#pragma once
#include <vector>
#include <memory>

class Engine;

class SceneComponent
{
public:
	SceneComponent() noexcept = default;

	virtual void Initialize(Engine* engine);
	virtual void Update();
	virtual void Render();	
	virtual ~SceneComponent() noexcept = default;
protected:
	Engine* engine = nullptr;
};