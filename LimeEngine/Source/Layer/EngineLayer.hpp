// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once

namespace LimeEngine
{
	class Engine;

	class EngineLayer
	{
		LE_DELETE_COPY(EngineLayer)

	private:
		static inline const char* LayerType = "EditorLayer";
		static inline std::vector<const char*> LayerDependencies = {};

	public:
		static Engine* GetEngine();
		static const std::vector<const char*>& GetLayerDependencies()
		{
			return LayerDependencies;
		}

	public:
		EngineLayer(const std::string& layerName) noexcept : layerName(layerName) {};
		EngineLayer() = default;
		virtual ~EngineLayer() = default;

		virtual void Init()
		{
			LE_CORE_LOG_TRACE("Init: {}", GetLayerName());
		}
		virtual void Begin()
		{
			LE_CORE_LOG_TRACE("Begin: {}", GetLayerName());
		}
		virtual void End()
		{
			LE_CORE_LOG_TRACE("End: {}", GetLayerName());
		}
		virtual void PreUpdate() {}
		virtual void Update() {}
		virtual void PostUpdate() {}
		virtual void DebugUpdate() {}

		const std::string& GetLayerName() const noexcept
		{
			return layerName;
		}

	private:
		std::string layerName = LayerType;
	};
}
