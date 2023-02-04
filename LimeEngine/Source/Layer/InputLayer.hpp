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