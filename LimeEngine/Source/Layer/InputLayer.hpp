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
	public:
		InputLayer(Engine* engine, InputDevice& inputDevice);

		void Update() override;
		InputDevice& GetInputDevice();

	private:
		InputDevice& inputDevice;
	};
}