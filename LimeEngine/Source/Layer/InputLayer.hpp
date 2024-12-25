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

	public:
		InputLayer() noexcept : EngineLayer("InputLayer") {};
		static InputLayer& GetInputLayer();

		void Update() override;
		InputDevice& GetInputDevice();

	private:
		InputDevice inputDevice;
	};
}
