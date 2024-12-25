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
		EngineLayer::Update();
		inputDevice.OnUpdate();
	}

	InputLayer& InputLayer::GetInputLayer()
	{
		return GetEngine().inputLayer;
	}

	InputDevice& InputLayer::GetInputDevice()
	{
		return inputDevice;
	}
}
