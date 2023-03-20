// Copyright (C) Pavel Jakushik - All Rights Reserved
// See file LICENSE for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "EngineLayer.hpp"
#include "Window/Window.hpp"

namespace LimeEngine
{
	class WindowLayer : public EngineLayer
	{
	public:
		WindowLayer(Engine* engine, std::unique_ptr<Window>&& window);

		void Update() override;
		Window& GetWindow() noexcept;

	private:
		std::unique_ptr<Window> window;
	};
}
