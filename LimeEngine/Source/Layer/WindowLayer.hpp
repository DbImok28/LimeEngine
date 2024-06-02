// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "EngineLayer.hpp"
#include "Window/Window.hpp"

namespace LimeEngine
{
	class WindowLayer : public EngineLayer
	{
		LE_DELETE_COPY(WindowLayer);

	public:
		WindowLayer() = default;
		~WindowLayer();

		static WindowLayer& GetWindowLayer();

		void Update() override;

		void SetWindow(URef<Window>&& window) noexcept;
		void SetWindow(const WindowArgs& windowArgs) noexcept;
		Window& GetWindow() noexcept;

	private:
		URef<Window> window;
	};
}
