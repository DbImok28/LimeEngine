#pragma once
#include "lepch.hpp"
#include "SceneLayer.hpp"

namespace LimeEngine
{
	SceneLayer::SceneLayer(Engine* engine) : EngineLayer(engine), scene(engine) {}

	void SceneLayer::Update()
	{
		scene.UpdateScene();
	}

	void SceneLayer::DebugUpdate()
	{
		scene.DebugUpdateScene();
	}

	Scene& SceneLayer::GetScene() noexcept
	{
		return scene;
	}
}
