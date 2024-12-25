// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once

namespace LimeEngine
{
	class Engine;

	class EngineLayer
	{
	public:
		EngineLayer(const std::string& layerName) noexcept : layerName(layerName) {};
		EngineLayer() = default;
		virtual ~EngineLayer() = default;
		static Engine& GetEngine();

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
		virtual void Update() {};
		virtual void DebugUpdate() {}

		const std::string& GetLayerName() const noexcept
		{
			return layerName;
		}

	private:
		std::string layerName = "EngineLayer";
	};
}
