// Developed by Pavel Jakushik. 
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#pragma once

#include "WinApi.hpp"
#include <optional>
#include <string>

#include "../Graphics/Graphics.hpp"
#include "../Input/InputDevice.hpp"
namespace LimeEngine
{
	class Engine;

	class Window
	{
	private:
		class WindowClass
		{
		public:
			WindowClass() noexcept;
			~WindowClass();
			WindowClass(const WindowClass&) = delete;
			WindowClass(WindowClass&&) noexcept = delete;
			WindowClass& operator=(const WindowClass&) = delete;
			WindowClass& operator=(WindowClass&&) noexcept = delete;

			static const wchar_t* GetName() noexcept;
			static HINSTANCE GetInstance() noexcept;
		private:
			static constexpr const wchar_t* name = L"GameEngineWindow";
			static WindowClass wndClassInstance;
			HINSTANCE hInst;
		};
	public:
		Window(Engine* engine, const wchar_t* title = L"GameEngine", int width = 1080, int height = 720);
		~Window();
		Window(const Window&) = delete;
		Window(Window&&) noexcept = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) noexcept = delete;

		void SetTitle(const std::wstring& title);
		std::optional<int> ProcessMessages() noexcept;

	private:
		static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		static LRESULT CALLBACK HandleMsgForwarding(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	public:
		int width;
		int height;
		Graphics graphics;
		InputDevice inputDevice;

	private:
		HWND hWnd;
	};
}