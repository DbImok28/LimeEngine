// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "lepch.hpp"
#include "InputLayer.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	void InputLayer::Update()
	{
		if (inputDevice) inputDevice->OnUpdate();
	}

	InputLayer& InputLayer::GetInputLayer()
	{
		return GetEngine().inputLayer;
	}

	void InputLayer::SetInputDevice(InputDevice* inputDevice)
	{
		this->inputDevice = inputDevice;
	}

	InputDevice& InputLayer::GetInputDevice()
	{
		return *inputDevice;
	}
}
