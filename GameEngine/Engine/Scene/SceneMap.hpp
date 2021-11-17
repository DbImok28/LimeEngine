#pragma once
#include "SceneObject.hpp"

class SceneMap
{
public:
	virtual void Initialize(Engine* engine);
	virtual void Update();
	virtual void Render();

	void InitializeObjects();
	void UpdateObjects();
	void RenderObjects();
	void AttachObject(std::unique_ptr<SceneObject>&& object);

	virtual ~SceneMap() noexcept = default;
public:
	std::vector<std::unique_ptr<SceneObject>> objects;
protected:
	Engine* engine = nullptr;
};