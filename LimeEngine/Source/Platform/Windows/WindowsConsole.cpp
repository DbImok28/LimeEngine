// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "WindowsConsole.hpp"

namespace LimeEngine
{
	WindowsConsole::WindowsConsole(const ConsoleArgs& args)
	{
		Open(args);
	}

	WindowsConsole::~WindowsConsole()
	{
		Close();
	}

	bool WindowsConsole::Open(const ConsoleArgs& args)
	{
		if (hConsole != nullptr)
		{
			Close();
		}
		bool result = false;
		if (AllocConsole())
		{
			SetTitle(args.title);
			SetMinLength(args.minLength);
			result = RedirectIO();
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		}
		std::ios::sync_with_stdio();
		return result;
	}

	bool WindowsConsole::Close() noexcept
	{
		bool result = ReleaseIO();
		if (!static_cast<bool>(FreeConsole()))
		{
			result = false;
			hConsole = nullptr;
		}
		return result;
	}

	void WindowsConsole::Print(tstring_view msg, PrimaryColor color) noexcept
	{
		SetConsoleTextAttribute(hConsole, static_cast<WORD>(color) | FOREGROUND_INTENSITY);

		DWORD written = 0;
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), msg.data(), static_cast<DWORD>(msg.length()), &written, NULL);
	}

	void WindowsConsole::SetTitle(const tstring& title) noexcept
	{
		SetConsoleTitle(title.c_str());
	}

	void WindowsConsole::SetMinLength(int16 minLength) const noexcept
	{
		CONSOLE_SCREEN_BUFFER_INFO conInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &conInfo);
		if (conInfo.dwSize.Y < minLength) conInfo.dwSize.Y = minLength;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), conInfo.dwSize);
	}

	bool RedirectIOHandle(DWORD stdHandle, const char* fileName, const char* openMode, FILE* stream) noexcept
	{
		bool result = true;
		FILE* fp;
		if (GetStdHandle(stdHandle) != INVALID_HANDLE_VALUE)
			if (freopen_s(&fp, fileName, openMode, stream) != 0)
				result = false;
			else
				setvbuf(stream, NULL, _IONBF, 0);
		return result;
	}

	bool WindowsConsole::RedirectIO() const noexcept
	{
		bool result = true;
		if (!RedirectIOHandle(STD_OUTPUT_HANDLE, "CONOUT$", "w", stdout)) result = false;
		if (!RedirectIOHandle(STD_INPUT_HANDLE, "CONIN$", "r", stdin)) result = false;
		if (!RedirectIOHandle(STD_ERROR_HANDLE, "CONOUT$", "w", stderr)) result = false;
		return result;
	}

	bool ReleaseIOHandle(const char* openMode, FILE* stream) noexcept
	{
		bool result = true;
		FILE* fp;
		if (freopen_s(&fp, "NUL:", openMode, stream) != 0)
			result = false;
		else
			setvbuf(stream, NULL, _IONBF, 0);
		return result;
	}

	bool WindowsConsole::ReleaseIO() const noexcept
	{
		bool result = true;
		if (!ReleaseIOHandle("w", stdout)) result = false;
		if (!ReleaseIOHandle("r", stdin)) result = false;
		if (!ReleaseIOHandle("w", stderr)) result = false;
		return result;
	}
}