#pragma once
#include "../Window/Window.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"

class InputDevice
{
	friend class Window;
public:
	Keyboard keyboard;
	Mouse mouse;
};