// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "EngineLayer.hpp"
#include "Input/InputDevice.hpp"

namespace LimeEngine
{
	class InputLayer : public EngineLayer
	{
		LE_DELETE_COPY(InputLayer);

	private:
		static inline const char* LayerType = "InputLayer";
		static inline std::vector<const char*> LayerDependencies;

	public:
		static const std::vector<const char*>& GetLayerDependencies()
		{
			return LayerDependencies;
		}

	public:
		InputLayer() noexcept : EngineLayer(LayerType) {};
		static InputLayer* GetInputLayer();

		void Update() override;
		InputDevice* GetInputDevice();

	private:
		InputDevice inputDevice;
	};
}
