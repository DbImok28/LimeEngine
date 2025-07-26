// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Utility/Timer.hpp"
#include "Layer/EngineLayerManager.hpp"
#include "Layer/DataLayer.hpp"
#include "Layer/WindowLayer.hpp"
#include "Layer/InputLayer.hpp"
#include "Layer/RenderLayer.hpp"
#include "Layer/SceneLayer.hpp"
#include "Layer/EditorLayer.hpp"

namespace LimeEngine
{
	LE_DECLARE_EXTERN_LOGGER(LogEngine);

	class Engine
	{
		LE_DELETE_MOVE_COPY(Engine)

	public:
		Engine();

		int Start();
		void UpdateLayers();

		void Close(int exitCode = 0);
		void Close(const Event& e);

	private:
		std::optional<int> exitCode;

	public:
		InputLayer* inputLayer;
		WindowLayer* windowLayer;
		DataLayer* dataLayer;
		RenderLayer* renderLayer;
		SceneLayer* sceneLayer;
		EditorLayer* editorLayer;

		EngineLayerManager layerManager;

		Timer timer;
		float deltaTime = 0.0f;

	public:
		static void Initialize();
		static Engine* GetEngine() noexcept;

	private:
		static Engine engine;
	};
}