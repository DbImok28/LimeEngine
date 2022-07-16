#include "Console.hpp"
#include <cstdio>
#include <fcntl.h>
#include <io.h>
#include <iostream>

namespace LimeEngine
{
	bool ConsoleWindows::Open(int16 minLength, const tstring& title) noexcept
	{
		bool result = false;
		Close();
		if (AllocConsole())
		{
			SetMinLength(minLength);
			result = RedirectAllIO();
			SetTitle(title);
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		}
		std::ios::sync_with_stdio();
		return result;
	}

	bool ConsoleWindows::Close() noexcept
	{
		bool result = ReleaseAllIO();
		if (!static_cast<bool>(FreeConsole()))
		{
			result = false;
			hConsole = nullptr;
		}
		return result;
	}

	void ConsoleWindows::SetTitle(const tstring& title) noexcept
	{
		SetConsoleTitle(title.c_str());
	}

	void ConsoleWindows::Print(tstring_view msg, PrimaryColor color) noexcept
	{
		SetConsoleTextAttribute(hConsole, static_cast<DWORD>(color) | FOREGROUND_INTENSITY);
		std::cout << msg;
	}

	void ConsoleWindows::SetMinLength(int16 minLength) const noexcept
	{
		CONSOLE_SCREEN_BUFFER_INFO conInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &conInfo);
		if (conInfo.dwSize.Y < minLength) conInfo.dwSize.Y = minLength;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), conInfo.dwSize);
	}

	// Redirect

	bool ConsoleWindows::RedirectIO(DWORD stdHandle, const char* fileName, const char* openMode, FILE* stream) const noexcept
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

	bool ConsoleWindows::RedirectSTDOUT() const noexcept
	{
		return RedirectIO(STD_OUTPUT_HANDLE, "CONOUT$", "w", stdout);
	}

	bool ConsoleWindows::RedirectSTDIN() const noexcept
	{
		return RedirectIO(STD_INPUT_HANDLE, "CONIN$", "r", stdin);
	}

	bool ConsoleWindows::RedirectSTDERR() const noexcept
	{
		return RedirectIO(STD_ERROR_HANDLE, "CONOUT$", "w", stderr);
	}

	bool ConsoleWindows::RedirectAllIO() const noexcept
	{
		bool result = true;
		if (!RedirectSTDOUT()) result = false;
		if (!RedirectSTDIN()) result = false;
		if (!RedirectSTDERR()) result = false;
		return result;
	}

	// Release

	bool ConsoleWindows::ReleaseIO(const char* openMode, FILE* stream) const noexcept
	{
		bool result = true;
		FILE* fp;
		if (freopen_s(&fp, "NUL:", openMode, stream) != 0)
			result = false;
		else
			setvbuf(stream, NULL, _IONBF, 0);
		return result;
	}

	bool ConsoleWindows::ReleaseSTDOUT() const noexcept
	{
		return ReleaseIO("w", stdout);
	}

	bool ConsoleWindows::ReleaseSTDIN() const noexcept
	{
		return ReleaseIO("r", stdin);
	}

	bool ConsoleWindows::ReleaseSTDERR() const noexcept
	{
		return ReleaseIO("w", stderr);
	}

	bool ConsoleWindows::ReleaseAllIO() const noexcept
	{
		bool result = true;
		if (!ReleaseSTDOUT()) result = false;
		if (!ReleaseSTDIN()) result = false;
		if (!ReleaseSTDERR()) result = false;
		return result;
	}
}