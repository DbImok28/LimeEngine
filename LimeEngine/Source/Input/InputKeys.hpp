// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once

namespace LimeEngine
{
	enum class InputKey
	{
		None = 0,
		LeftMouseButton = 0x01,   // Left mouse button
		RightMouseButton = 0x02,  // Right mouse button
		CtrlBrkPrcs = 0x03,       // Control-break processing
		MiddleMouseButton = 0x04, // Middle mouse button

		ThumbForwardMouseButton = 0x05, // Thumb button back on mouse aka X1
		ThumbBackMouseButton = 0x06,    // Thumb button forward on mouse aka X2

		BackSpace = 0x08, // Backspace key
		Tab = 0x09,       // Tab key

		Clear = 0x0C, // Clear key
		Enter = 0x0D, // Enter or Return key

		Pause = 0x13,    // Pause key
		CapsLock = 0x14, // Caps lock key

		Escape = 0x1B, // Esc key

		Convert = 0x1C,    // IME convert
		NonConvert = 0x1D, // IME Non convert
		Accept = 0x1E,     // IME accept
		ModeChange = 0x1F, // IME mode change

		Space = 0x20,       // Space bar
		PageUp = 0x21,      // Page up key
		PageDown = 0x22,    // Page down key
		End = 0x23,         // End key
		Home = 0x24,        // Home key
		LeftArrow = 0x25,   // Left arrow key
		UpArrow = 0x26,     // Up arrow key
		RightArrow = 0x27,  // Right arrow key
		DownArrow = 0x28,   // Down arrow key
		Select = 0x29,      // Select key
		Print = 0x2A,       // Print key
		Execute = 0x2B,     // Execute key
		PrintScreen = 0x2C, // Print screen key
		Insert = 0x2D,      // Insert key
		Delete = 0x2E,      // Delete key
		Help = 0x2F,        // Help key

		Num0 = 0x30, // Top row 0 key (Matches '0')
		Num1 = 0x31, // Top row 1 key (Matches '1')
		Num2 = 0x32, // Top row 2 key (Matches '2')
		Num3 = 0x33, // Top row 3 key (Matches '3')
		Num4 = 0x34, // Top row 4 key (Matches '4')
		Num5 = 0x35, // Top row 5 key (Matches '5')
		Num6 = 0x36, // Top row 6 key (Matches '6')
		Num7 = 0x37, // Top row 7 key (Matches '7')
		Num8 = 0x38, // Top row 8 key (Matches '8')
		Num9 = 0x39, // Top row 9 key (Matches '9')

		A = 0x41, // A key (Matches 'A')
		B = 0x42, // B key (Matches 'B')
		C = 0x43, // C key (Matches 'C')
		D = 0x44, // D key (Matches 'D')
		E = 0x45, // E key (Matches 'E')
		F = 0x46, // F key (Matches 'F')
		G = 0x47, // G key (Matches 'G')
		H = 0x48, // H key (Matches 'H')
		I = 0x49, // I key (Matches 'I')
		J = 0x4A, // J key (Matches 'J')
		K = 0x4B, // K key (Matches 'K')
		L = 0x4C, // L key (Matches 'L')
		M = 0x4D, // M key (Matches 'M')
		N = 0x4E, // N key (Matches 'N')
		O = 0x4F, // O key (Matches 'O')
		P = 0x50, // P key (Matches 'P')
		Q = 0x51, // Q key (Matches 'Q')
		R = 0x52, // R key (Matches 'R')
		S = 0x53, // S key (Matches 'S')
		T = 0x54, // T key (Matches 'T')
		U = 0x55, // U key (Matches 'U')
		V = 0x56, // V key (Matches 'V')
		W = 0x57, // W key (Matches 'W')
		X = 0x58, // X key (Matches 'X')
		Y = 0x59, // Y key (Matches 'Y')
		Z = 0x5A, // Z key (Matches 'Z')

		LeftWin = 0x5B,  // Left windows key
		RightWin = 0x5C, // Right windows key
		Apps = 0x5D,     // Applications key

		Sleep = 0x5F, // Computer sleep key

		Numpad0 = 0x60,   // Numpad 0
		Numpad1 = 0x61,   // Numpad 1
		Numpad2 = 0x62,   // Numpad 2
		Numpad3 = 0x63,   // Numpad 3
		Numpad4 = 0x64,   // Numpad 4
		Numpad5 = 0x65,   // Numpad 5
		Numpad6 = 0x66,   // Numpad 6
		Numpad7 = 0x67,   // Numpad 7
		Numpad8 = 0x68,   // Numpad 8
		Numpad9 = 0x69,   // Numpad 9
		Multiply = 0x6A,  // Multiply key
		Add = 0x6B,       // Add key
		Separator = 0x6C, // Separator key
		Subtract = 0x6D,  // Subtract key
		Decimal = 0x6E,   // Decimal key
		Divide = 0x6F,    // Divide key
		F1 = 0x70,        // F1
		F2 = 0x71,        // F2
		F3 = 0x72,        // F3
		F4 = 0x73,        // F4
		F5 = 0x74,        // F5
		F6 = 0x75,        // F6
		F7 = 0x76,        // F7
		F8 = 0x77,        // F8
		F9 = 0x78,        // F9
		F10 = 0x79,       // F10
		F11 = 0x7A,       // F11
		F12 = 0x7B,       // F12
		F13 = 0x7C,       // F13
		F14 = 0x7D,       // F14
		F15 = 0x7E,       // F15
		F16 = 0x7F,       // F16
		F17 = 0x80,       // F17
		F18 = 0x81,       // F18
		F19 = 0x82,       // F19
		F20 = 0x83,       // F20
		F21 = 0x84,       // F21
		F22 = 0x85,       // F22
		F23 = 0x86,       // F23
		F24 = 0x87,       // F24

		NavigationView = 0x88,   // Reserved
		NavigationMenu = 0x89,   // Reserved
		NavigationUp = 0x8A,     // Reserved
		NavigationDown = 0x8B,   // Reserved
		NavigationLeft = 0x8C,   // Reserved
		NavigationRight = 0x8D,  // Reserved
		NavigationAccept = 0x8E, // Reserved
		NavigationCancel = 0x8F, // Reserved

		NumLock = 0x90,    // Num lock key
		ScrollLock = 0x91, // Scroll lock key

		NumpadEqual = 0x92, // Numpad =

		LeftShift = 0xA0,  // Left shift key
		RightShift = 0xA1, // Right shift key
		LeftCtrl = 0xA2,   // Left control key
		RightCtrl = 0xA3,  // Right control key
		LeftMenu = 0xA4,   // Left menu key
		RightMenu = 0xA5,  // Right menu

		BrowserBack = 0xA6,      // Browser back button
		BrowserForward = 0xA7,   // Browser forward button
		BrowserRefresh = 0xA8,   // Browser refresh button
		BrowserStop = 0xA9,      // Browser stop button
		BrowserSearch = 0xAA,    // Browser search button
		BrowserFavorites = 0xAB, // Browser favorites button
		BrowserHome = 0xAC,      // Browser home button

		VolumeMute = 0xAD,  // Volume mute button
		VolumeDown = 0xAE,  // Volume down button
		VolumeUp = 0xAF,    // Volume up button
		NextTrack = 0xB0,   // Next track media button
		PrevTrack = 0xB1,   // Previous track media button
		Stop = 0xB2,        // Stop media button
		PlayPause = 0xB3,   // Play/pause media button
		Mail = 0xB4,        // Launch mail button
		MediaSelect = 0xB5, // Launch media select button
		App1 = 0xB6,        // Launch app 1 button
		App2 = 0xB7,        // Launch app 2 button

		Semicolon = 0xBA,   // ;
		Plus = 0xBB,        // Plus key
		Comma = 0xBC,       // Comma key
		Minus = 0xBD,       // Minus key
		Period = 0xBE,      // Period key
		Slash = 0xBF,       // /
		GraveAccent = 0xC0, // `

		GamepadA = 0xC3,                // Gamepad A button
		GamepadB = 0xC4,                // Gamepad B button
		GamepadX = 0xC5,                // Gamepad X button
		GamepadY = 0xC6,                // Gamepad Y button
		GamepadRightBumper = 0xC7,      // Gamepad right bumper
		GamepadLeftBumper = 0xC8,       // Gamepad left bumper
		GamepadLeftTrigger = 0xC9,      // Gamepad left trigger
		GamepadRightTrigger = 0xCA,     // Gamepad right trigger
		GamepadDPadUp = 0xCB,           // Gamepad DPad up
		GamepadDPadDown = 0xCC,         // Gamepad DPad down
		GamepadDPadLeft = 0xCD,         // Gamepad DPad left
		GamepadDPadRight = 0xCE,        // Gamepad DPad right
		GamepadMenu = 0xCF,             // Gamepad menu button
		GamepadView = 0xD0,             // Gamepad view button
		GamepadLeftStickButton = 0xD1,  // Gamepad left stick button
		GamepadRightStickButton = 0xD2, // Gamepad right stick button
		GamepadLeftStickUp = 0xD3,      // Gamepad left stick up
		GamepadLeftStickDown = 0xD4,    // Gamepad left stick down
		GamepadLeftStickRight = 0xD5,   // Gamepad left stick right
		GamepadLeftStickLeft = 0xD6,    // Gamepad left stick left
		GamepadRightStickUp = 0xD7,     // Gamepad right stick up
		GamepadRightStickDown = 0xD8,   // Gamepad right stick down
		GamepadRightStickRight = 0xD9,  // Gamepad right stick right
		GamepadRightStickLeft = 0xDA,   // Gamepad right stick left

		LeftBracket = 0xDB,  // [ for US or misc keys for others
		Backslash = 0xDC,    // \ for US or misc keys for others
		RightBracket = 0xDD, // ] for US or misc keys for others
		Apostrophe = 0xDE,   // ' for US or misc keys for others
		OEM8 = 0xDF,         // Misc keys for others

		// Actions
		WheelUp,
		WheelDown,
		MouseMoveX,
		MouseMoveY,
	};

	std::string InputKeyToString(InputKey key) noexcept;
}
