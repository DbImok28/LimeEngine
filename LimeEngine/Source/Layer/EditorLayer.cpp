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
