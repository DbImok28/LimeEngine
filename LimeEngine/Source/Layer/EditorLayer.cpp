// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "lepch.hpp"
#include "EditorLayer.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	EditorLayer::EditorLayer(Engine* engine) : EngineLayer(engine) {}

	void EditorLayer::Update()
	{
		engine->sceneLayer.DebugUpdate();
	}
}
