// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "lepch.hpp"
#include "InputLayer.hpp"

namespace LimeEngine
{
	InputLayer::InputLayer(Engine* engine, InputDevice& inputDevice) : EngineLayer(engine), inputDevice(inputDevice) {}

	void InputLayer::Update()
	{
		inputDevice.OnUpdate();
	}

	InputDevice& InputLayer::GetInputDevice()
	{
		return inputDevice;
	}
}