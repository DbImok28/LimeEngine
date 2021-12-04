#pragma once
#include <vector>
#include <memory>

#include "../Base/Transformable.hpp"

class Engine;
class SceneObject;

class SceneComponent : public Transformable
{
public:
	SceneComponent() noexcept = default;

	virtual void Initialize(Engine* engine, SceneObject* rootObject);
	virtual void Update();
	virtual void Render();	
	virtual ~SceneComponent() noexcept = default;
	TempTransformMatrix GetWorldTransformMatrix() const noexcept override;

protected:
	SceneObject* rootObject = nullptr;
	Engine* engine = nullptr;
};