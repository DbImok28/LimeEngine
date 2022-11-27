#pragma once
#include "Window/Windows/WinApi.hpp"
#include "Window/Base/Console.hpp"
#include <map>

namespace LimeEngine
{
	class ConsoleWindows : public Console
	{
	public:
		void SetMinLength(int16 minLength) const noexcept;

		virtual bool Open(int16 minLength, const tstring& title) noexcept override;
		virtual bool Close() noexcept override;
		virtual void SetTitle(const tstring& title) noexcept override;
		virtual void Print(tstring_view msg, PrimaryColor color = PrimaryColor::Gray) noexcept override;

	private:
		// Redirect
		bool RedirectIO(DWORD stdHandle, const char* fileName, const char* openMode, FILE* stream) const noexcept;
		bool RedirectSTDOUT() const noexcept;
		bool RedirectSTDIN() const noexcept;
		bool RedirectSTDERR() const noexcept;
		bool RedirectAllIO() const noexcept;

		// Release
		bool ReleaseIO(const char* openMode, FILE* stream) const noexcept;
		bool ReleaseSTDOUT() const noexcept;
		bool ReleaseSTDIN() const noexcept;
		bool ReleaseSTDERR() const noexcept;
		bool ReleaseAllIO() const noexcept;

	public:
		HANDLE hConsole = nullptr;
	};
}