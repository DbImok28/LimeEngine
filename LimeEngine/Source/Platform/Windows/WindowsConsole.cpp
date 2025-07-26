// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "WindowsConsole.hpp"
#include "WindowsExceptions.hpp"

namespace LimeEngine
{
	WindowsConsole::WindowsConsole(const ConsoleArgs& args) : hConsole(INVALID_HANDLE_VALUE)
	{
		WindowsConsole::Open(args);
	}

	WindowsConsole::~WindowsConsole()
	{
		WindowsConsole::Close();
	}

	bool WindowsConsole::Open(const ConsoleArgs& args)
	{
		if (AttachConsole(ATTACH_PARENT_PROCESS))
		{
			// Console is already open
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			CHECK_HR(hConsole != INVALID_HANDLE_VALUE);
			return false;
		}

		CHECK_LAST_ERROR(AllocConsole());
		LE_ASSERT(RedirectIO());

		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CHECK_HR(hConsole != INVALID_HANDLE_VALUE);

		SetTitle(args.title);
		SetMinLength(args.minLength);

		std::ios::sync_with_stdio();
		return true;
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
		WriteConsole(hConsole, msg.data(), static_cast<DWORD>(msg.length()), &written, NULL);
	}

	void WindowsConsole::SetTitle(const tstring& title)
	{
		CHECK_LAST_ERROR(SetConsoleTitle(title.c_str()) != 0);
	}

	void WindowsConsole::SetMinLength(int16 minLength) const
	{
		CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
		CHECK_LAST_ERROR(GetConsoleScreenBufferInfo(hConsole, &bufferInfo) != 0);
		if (bufferInfo.dwSize.Y < minLength) bufferInfo.dwSize.Y = minLength;

		CHECK_LAST_ERROR(SetConsoleScreenBufferSize(hConsole, bufferInfo.dwSize) != 0);
	}

	void* WindowsConsole::GetHandle() const noexcept
	{
		return hConsole;
	}

	bool RedirectIOHandle(DWORD stdHandle, const char* fileName, const char* openMode, FILE* stream)
	{
		auto handle = GetStdHandle(stdHandle);
		CHECK_HR(handle != INVALID_HANDLE_VALUE);

		FILE* fp;
		if (freopen_s(&fp, fileName, openMode, stream) != 0)
			return false;
		else
			setvbuf(stream, NULL, _IONBF, 0);
		return true;
	}

	bool WindowsConsole::RedirectIO() const
	{
		bool result = true;
		if (!RedirectIOHandle(STD_OUTPUT_HANDLE, "CONOUT$", "w", stdout)) result = false;
		if (!RedirectIOHandle(STD_INPUT_HANDLE, "CONIN$", "r", stdin)) result = false;
		if (!RedirectIOHandle(STD_ERROR_HANDLE, "CONOUT$", "w", stderr)) result = false;
		return result;
	}

	bool ReleaseIOHandle(const char* openMode, FILE* stream) noexcept
	{
		FILE* fp;
		if (freopen_s(&fp, "NUL:", openMode, stream) != 0)
			return false;
		else
			setvbuf(stream, NULL, _IONBF, 0);
		return true;
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