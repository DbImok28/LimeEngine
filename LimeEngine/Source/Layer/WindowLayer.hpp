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
		WindowLayer() : window(std::move(window)) {}
		WindowLayer(std::unique_ptr<Window>&& window) : window(std::move(window)) {}
		~WindowLayer();

		static WindowLayer& GetWindowLayer();

		void Update() override;

		Window& GetWindow() noexcept;
		void SetWindow(std::unique_ptr<Window>&& window) noexcept;

	private:
		std::unique_ptr<Window> window;
	};
}
