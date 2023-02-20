// Developed by Pavel Jakushik.
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Window/Window.hpp"
#include "WinApi.hpp"
#include "CoreBase.hpp"
#include "Exceptions/EngineExceptions.hpp"

#define WND_EXCEPTION(hr)    LimeEngine::WindowsWindowException(__LINE__, __FILE__, hr)
#define WND_LAST_EXCEPTION() LimeEngine::WindowsWindowException(__LINE__, __FILE__, GetLastError())

namespace LimeEngine
{
	class WindowsWindowException : public EngineHrException
	{
		using EngineHrException::EngineHrException;

	public:
		virtual const char* GetType() const noexcept override
		{
			return "WindowsWindowException";
		}
	};

	class WindowsWindow : public Window
	{
	private:
		class WindowClass
		{
		public:
			WindowClass() noexcept;
			~WindowClass();

			static const TCHAR* GetName() noexcept;
			static HINSTANCE GetInstance() noexcept;

		private:
			static constexpr const TCHAR* name = TEXT("LimeEngineWindow");
			static WindowClass wndClassInstance;
			HINSTANCE hInst;
		};

	public:
		WindowsWindow() = default;
		WindowsWindow(const WindowArgs& args);
		virtual ~WindowsWindow();

		void Init(const WindowArgs& args) override;
		void Destroy() override;
		void OnUpdate() override;
		void SetTitle(const tstring& title) override;
		uint GetWidth() const noexcept override
		{
			return width;
		}
		uint GetHeight() const noexcept override
		{
			return height;
		}
		void* GetHandle() const noexcept override;

	private:
		static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		static LRESULT CALLBACK HandleMsgForwarding(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	public:
		int width;
		int height;

	private:
		HWND hWnd = nullptr;
	};
}