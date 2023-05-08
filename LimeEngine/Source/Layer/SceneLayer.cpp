#pragma once
#include "lepch.hpp"
#include "SceneLayer.hpp"

namespace LimeEngine
{
	void SceneLayer::Update()
	{
		scene->UpdateSubPrimaryComponents();
	}

	void SceneLayer::DebugUpdate()
	{
		scene->DebugUpdateSubPrimaryComponents();
	}

	Scene& SceneLayer::GetScene() noexcept
	{
		return *scene;
	}
}
