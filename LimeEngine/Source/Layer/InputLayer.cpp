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