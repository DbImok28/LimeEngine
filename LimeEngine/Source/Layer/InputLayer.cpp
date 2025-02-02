// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "lepch.hpp"
#include "InputLayer.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	InputLayer* InputLayer::GetInputLayer()
	{
		return GetEngine()->inputLayer;
	}

	void InputLayer::Update()
	{
		EngineLayer::Update();
		inputDevice.OnUpdate();
	}

	InputDevice* InputLayer::GetInputDevice()
	{
		return &inputDevice;
	}
}
