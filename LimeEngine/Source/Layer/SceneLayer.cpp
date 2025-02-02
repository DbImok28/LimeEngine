// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "lepch.hpp"
#include "SceneLayer.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	SceneLayer* SceneLayer::GetSceneLayer()
	{
		return GetEngine()->sceneLayer;
	}

	void SceneLayer::Init()
	{
		EngineLayer::Init();
		scene->PropagateInit();
	}

	void SceneLayer::Begin()
	{
		EngineLayer::Begin();
		scene->PropagateBegin();
	}

	void SceneLayer::End()
	{
		EngineLayer::End();
		scene->DestroyImmediately();
	}

	void SceneLayer::Update()
	{
		EngineLayer::Update();
		scene->PropagateUpdate();
	}

	void SceneLayer::DebugUpdate()
	{
		EngineLayer::DebugUpdate();
		if (RuntimeEditor::BeginPanel("Properties"))
		{
			for (auto& map : scene->GetSubMaps())
			{
				for (auto& object : map->GetSubObjects())
				{
					if (object != nullptr)
					{
						Transform transform = object->GetTransform();
						RuntimeEditor::Input(object->GetObjectName(), transform);
						object->SetTransform(transform);

						for (auto& component : object->GetSubComponents())
						{
							transform = component->GetTransform();
							RuntimeEditor::Input(std::format("{}/{}", object->GetObjectName(), component->GetComponentName()), transform);
							component->SetTransform(transform);
						}
					}
				}
			}
			RuntimeEditor::EndPanel();
		}

		if (RuntimeEditor::BeginPanel("Info"))
		{
			for (auto& map : scene->GetSubMaps())
			{
				for (auto& object : map->GetSubObjects())
				{
					RuntimeEditor::Text(object->GetObjectName(), std::format("{}", object->GetObjectTransform()));
				}
			}
			RuntimeEditor::EndPanel();
		}

		scene->PropagateDebugUpdate();
	}

	Scene* SceneLayer::GetScene() noexcept
	{
		return scene.get();
	}
}
