// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Utility/Timer.hpp"
#include "Layer/DataLayer.hpp"
#include "Layer/WindowLayer.hpp"
#include "Layer/InputLayer.hpp"
#include "Layer/RenderLayer.hpp"
#include "Layer/SceneLayer.hpp"
#include "Layer/EditorLayer.hpp"

namespace LimeEngine
{
	class Engine
	{
		LE_DELETE_MOVE_COPY(Engine)

	public:
		Engine(std::unique_ptr<Window>&& window);
		virtual ~Engine();

		int Start();
		void UpdateLayers();

		void Close(int exitCode = 0);

	private:
		void Close(const Event& e);

	private:
		std::optional<int> exitCode;

	public:
		WindowLayer windowLayer;
		InputLayer inputLayer;
		RenderLayer renderLayer;
		DataLayer dataLayer;
		SceneLayer sceneLayer;
		EditorLayer editorLayer;

		Timer timer;
		float deltaTime = 0.0f;
	};
}