#pragma once
#include "../WinApi.hpp"
#include "../../../CoreBase.hpp"
#include <cstdio>
#include <fcntl.h>
#include <io.h>
#include <iostream>

namespace LimeEngine
{
	class ConsoleWindows
	{
	public:
		bool Open(int16_t minLength)
		{
			bool result = false;
			Close();
			if (AllocConsole())
			{
				AdjustConsoleBuffer(minLength);
				result = RedirectAllIO();
			}
			std::ios::sync_with_stdio();
			return result;
		}
		bool Open(int16_t minLength, const tstring& title)
		{
			if (Open(minLength))
			{
				SetTitle(title);
				return true;
			}
			else
			{
				return false;
			}
		}
		bool Close()
		{
			bool result = ReleaseAllIO();
			if (!static_cast<bool>(FreeConsole())) result = false;
			return result;
		}
		void SetTitle(const tstring& title)
		{
			SetConsoleTitle(title.c_str());
		}
		void AdjustConsoleBuffer(int16 minLength)
		{
			// Set the screen buffer to be big enough to scroll some text
			CONSOLE_SCREEN_BUFFER_INFO conInfo;
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &conInfo);
			if (conInfo.dwSize.Y < minLength) conInfo.dwSize.Y = minLength;
			SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), conInfo.dwSize);
		}

	private:
		// Redirect
		bool RedirectIO(DWORD stdHandle, const char* fileName, const char* openMode, FILE* stream)
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
		bool RedirectSTDOUT()
		{
			return RedirectIO(STD_OUTPUT_HANDLE, "CONOUT$", "w", stdout);
		}
		bool RedirectSTDIN()
		{
			return RedirectIO(STD_INPUT_HANDLE, "CONIN$", "r", stdin);
		}
		bool RedirectSTDERR()
		{
			return RedirectIO(STD_ERROR_HANDLE, "CONOUT$", "w", stderr);
		}
		bool RedirectAllIO()
		{
			bool result = true;
			if (!RedirectSTDOUT()) result = false;
			if (!RedirectSTDIN()) result = false;
			if (!RedirectSTDERR()) result = false;
			return result;
		}

		// Release
		bool ReleaseIO(const char* openMode, FILE* stream)
		{
			bool result = true;
			FILE* fp;
			if (freopen_s(&fp, "NUL:", openMode, stream) != 0)
				result = false;
			else
				setvbuf(stream, NULL, _IONBF, 0);
			return result;
		}
		bool ReleaseSTDOUT()
		{
			return ReleaseIO("w", stdout);
		}
		bool ReleaseSTDIN()
		{
			return ReleaseIO("r", stdin);
		}
		bool ReleaseSTDERR()
		{
			return ReleaseIO("w", stderr);
		}
		bool ReleaseAllIO()
		{
			bool result = true;
			if (!ReleaseSTDOUT()) result = false;
			if (!ReleaseSTDIN()) result = false;
			if (!ReleaseSTDERR()) result = false;
			return result;
		}
	};
}
