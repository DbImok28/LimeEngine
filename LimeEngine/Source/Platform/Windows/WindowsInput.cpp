// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "WindowsInput.hpp"

namespace LimeEngine
{
	std::optional<LRESULT> WindowsInput::HandleInputMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
			case WM_KILLFOCUS:
			{
				ClearKeyState();
				break;
			}
			// Keyboard
			case WM_SYSKEYDOWN:
			case WM_KEYDOWN:
			{
				auto key = static_cast<InputKey>(wParam);
				if (GetInputDevice().keyboard.IsKeysAutoRepeat())
				{
					OnKeyboardKeyPressed(key);
				}
				else
				{
					const bool wasPressed = lParam & 0x40000000;
					if (!wasPressed)
					{
						switch (wParam)
						{
							case VK_SHIFT:
							{
								UINT scancode = static_cast<UINT>((lParam & 0x00ff0000) >> 16);
								OnKeyboardKeyPressed(static_cast<InputKey>(MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX)));
								break;
							}
							case VK_CONTROL:
							{
								int extended = (lParam & 0x01000000) != 0;
								OnKeyboardKeyPressed(static_cast<InputKey>(extended ? InputKey::RightCtrl : InputKey::LeftCtrl));
								break;
							}
							case VK_MENU:
							{
								int extended = (lParam & 0x01000000) != 0;
								OnKeyboardKeyPressed(static_cast<InputKey>(extended ? InputKey::LeftMenu : InputKey::RightMenu));
								break;
							}
							default:
							{
								OnKeyboardKeyPressed(key);
								break;
							}
						}
					}
				}
				break;
			}
			case WM_SYSKEYUP:
			case WM_KEYUP:
			{
				auto key = static_cast<InputKey>(wParam);
				switch (wParam)
				{
					case VK_SHIFT:
					{
						UINT scancode = static_cast<UINT>((lParam & 0x00ff0000) >> 16);
						OnKeyboardKeyReleased(static_cast<InputKey>(MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX)));
						break;
					}
					case VK_CONTROL:
					{
						int extended = (lParam & 0x01000000) != 0;
						OnKeyboardKeyReleased(static_cast<InputKey>(extended ? InputKey::RightCtrl : InputKey::LeftCtrl));
						break;
					}
					case VK_MENU:
					{
						int extended = (lParam & 0x01000000) != 0;
						OnKeyboardKeyReleased(static_cast<InputKey>(extended ? InputKey::LeftMenu : InputKey::RightMenu));
						break;
					}
					default:
					{
						OnKeyboardKeyReleased(key);
						break;
					}
				}
				break;
			}
			case WM_CHAR:
			{
				auto ch = static_cast<wchar_t>(wParam);
				if (GetInputDevice().keyboard.IsCharsAutoRepeat())
				{
					OnKeyboardChar(ch);
				}
				else
				{
					const bool wasPressed = lParam & 0x40000000;
					if (!wasPressed)
					{
						OnKeyboardChar(ch);
					}
				}
				break;
			}

			// Mouse
			case WM_MOUSEMOVE:
			{
				const POINTS pt = MAKEPOINTS(lParam);
				OnMouseMove(pt.x, pt.y);

				RECT windowRect;
				::GetWindowRect(hWnd, &windowRect);
				auto width = windowRect.right - windowRect.left;
				auto height = windowRect.bottom - windowRect.top;
				if (pt.x >= 0 && pt.x < width && pt.y >= 0 && pt.y < height)
				{
					if (!GetInputDevice().mouse.IsInWindow())
					{
						SetCapture(hWnd);
						OnMouseEnter();
					}
				}
				else
				{
					if (GetInputDevice().mouse.IsInWindow())
					{
						ReleaseCapture();
						OnMouseLeave();
					}
				}
				break;
			}
			case WM_LBUTTONDBLCLK:
			case WM_LBUTTONDOWN:
			{
				const POINTS pt = MAKEPOINTS(lParam);
				OnMouseKeyPressed(InputKey::LeftMouseButton, pt.x, pt.y);
				break;
			}
			case WM_RBUTTONDBLCLK:
			case WM_RBUTTONDOWN:
			{
				const POINTS pt = MAKEPOINTS(lParam);
				OnMouseKeyPressed(InputKey::RightMouseButton, pt.x, pt.y);
				break;
			}
			case WM_MBUTTONDBLCLK:
			case WM_MBUTTONDOWN:
			{
				const POINTS pt = MAKEPOINTS(lParam);
				OnMouseKeyPressed(InputKey::MiddleMouseButton, pt.x, pt.y);
				break;
			}
			case WM_XBUTTONDBLCLK:
			case WM_XBUTTONDOWN:
			{
				const POINTS pt = MAKEPOINTS(lParam);
				InputKey key = (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? InputKey::ThumbForwardMouseButton : InputKey::ThumbBackMouseButton;
				OnMouseKeyPressed(key, pt.x, pt.y);
				break;
			}

			case WM_LBUTTONUP:
			{
				const POINTS pt = MAKEPOINTS(lParam);
				OnMouseKeyReleased(InputKey::LeftMouseButton, pt.x, pt.y);
				break;
			}
			case WM_RBUTTONUP:
			{
				const POINTS pt = MAKEPOINTS(lParam);
				OnMouseKeyReleased(InputKey::RightMouseButton, pt.x, pt.y);
				break;
			}
			case WM_MBUTTONUP:
			{
				const POINTS pt = MAKEPOINTS(lParam);
				OnMouseKeyReleased(InputKey::MiddleMouseButton, pt.x, pt.y);
				break;
			}
			case WM_XBUTTONUP:
			{
				const POINTS pt = MAKEPOINTS(lParam);
				InputKey key = (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? InputKey::ThumbForwardMouseButton : InputKey::ThumbBackMouseButton;
				OnMouseKeyReleased(key, pt.x, pt.y);
				break;
			}
			case WM_MOUSEWHEEL:
			{
				const POINTS pt = MAKEPOINTS(lParam);
				auto delta = static_cast<float>(GET_WHEEL_DELTA_WPARAM(wParam)) / static_cast<float>(WHEEL_DELTA);
				OnMouseWheelDelta(pt.x, pt.y, delta);
				break;
			}
			case WM_INPUT:
			{
				UINT dataSize = 0u;
				GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));
				if (dataSize > 0u)
				{
					std::unique_ptr<BYTE[]> rawdata = std::make_unique<BYTE[]>(dataSize);
					if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, rawdata.get(), &dataSize, sizeof(RAWINPUTHEADER)) == dataSize)
					{
						RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawdata.get());
						if (raw->header.dwType == RIM_TYPEMOUSE)
						{
							OnMouseRawMove(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
						}
					}
				}
				break;
			}
		}
		return std::nullopt;
	}
}
