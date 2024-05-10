// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "IBindable.hpp"
#include "Window/Window.hpp"

namespace LimeEngine
{
	enum class DisplayMode
	{
		Windowed,
		FullscreenWindowed,
		FullscreenExclusive
	};

	class RenderOutputArgs
	{
	public:
		RenderOutputArgs(Window* window, DisplayMode mode = DisplayMode::Windowed, bool defaultFullscreenModeIsExclusive = false) noexcept :
			window(window), mode(mode), defaultFullscreenModeIsExclusive(defaultFullscreenModeIsExclusive)
		{}

		Window* window = nullptr;
		DisplayMode mode = DisplayMode::Windowed;
		bool defaultFullscreenModeIsExclusive = false;
	};

	class RenderOutput : public IBindable
	{
	public:
		virtual ~RenderOutput();

	public:
		virtual void Init(const RenderOutputArgs& args) = 0;

		virtual void Create() = 0;
		virtual void Destroy() = 0;
		virtual void Present() = 0;

		virtual void Resize(uint width, uint height) = 0;

	protected:
		virtual void OnResize(uint width, uint height) = 0;

	private:
		void OnResizeEvent(const Event& e);

	public:
		void SetupDisplayMode(DisplayMode mode, bool isExclusive);
		void SetDefaultFullscreenMode(bool isExclusive) noexcept;

		Window* GetWindow() noexcept;
		void SetWindow(Window* newWindow);

		uint GetWidth() const noexcept;
		uint GetHeight() const noexcept;

		DisplayMode GetDisplayMode() const noexcept;
		virtual void SetDisplayMode(DisplayMode mode) = 0;

	protected:
		Window* window = nullptr;
		bool defaultFullscreenModeIsExclusive = false;
		DisplayMode displayMode = DisplayMode::Windowed;
	};
}
