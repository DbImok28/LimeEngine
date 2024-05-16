// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "lepch.hpp"
#include "SceneLayer.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	SceneLayer& SceneLayer::GetSceneLayer()
	{
		return GetEngine().sceneLayer;
	}

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
