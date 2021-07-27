#pragma once
#include "Keyboard.hpp"
#include "Mouse.hpp"

class InputDevice
{
	friend class Window;
public:
	InputDevice(const InputDevice&) = delete;
	InputDevice& operator=(const InputDevice&) = delete;
	InputDevice() = default;

	Keyboard keyboard;
	Mouse mouse;
};