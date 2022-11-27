#pragma once
#include "Keyboard.hpp"
#include "Mouse.hpp"

namespace LimeEngine
{
	class InputDevice
	{
		friend class Window;

	public:
		// TODO: Add event system
		Keyboard keyboard;
		Mouse mouse;
	};
}