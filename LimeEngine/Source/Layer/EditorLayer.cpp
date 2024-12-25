// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "lepch.hpp"
#include "EditorLayer.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	EditorLayer& EditorLayer::GetEditorLayer()
	{
		return GetEngine().editorLayer;
	}

	void EditorLayer::Update()
	{
		EngineLayer::Update();
		outputLogPanel.Render();
	}

	void EditorLayer::DebugUpdate()
	{
		EngineLayer::DebugUpdate();
		GetEngine().sceneLayer.DebugUpdate();
	}
}
