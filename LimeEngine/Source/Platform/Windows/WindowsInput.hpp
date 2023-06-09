// Copyright (C) Pavel Jakushik - All Rights Reserved
// See file LICENSE for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Input/Input.hpp"
#include "WindowsWindow.hpp"

namespace LimeEngine
{
	class WindowsInput : public Input
	{
	public:
		virtual ~WindowsInput() = default;

		std::optional<LRESULT> HandleInputMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}
