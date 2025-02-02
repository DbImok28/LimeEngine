// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "EngineLayer.hpp"
#include "Window/Window.hpp"

namespace LimeEngine
{
	namespace
	{
		struct PendingWindowsToCloseParams
		{
			Window* window = nullptr;
			int exitCode = 0;
		};
	}

	class WindowLayer : public EngineLayer
	{
		LE_DELETE_COPY(WindowLayer);

	private:
		static inline const char* LayerType = "WindowLayer";
		static inline std::vector<const char*> LayerDependencies = { "InputLayer" };

	public:
		static const std::vector<const char*>& GetLayerDependencies()
		{
			return LayerDependencies;
		}

	public:
		WindowLayer() noexcept : EngineLayer(LayerType) {};
		virtual ~WindowLayer() override;
		static WindowLayer* GetWindowLayer();

		void Update() override;
		void PostUpdate() override;

		// TODO: rename to CreateWindow
		void AddWindow(const WindowArgs& windowArgs);
		void AddWindow(URef<Window>&& window);
		Window* GetWindow(int index) noexcept;

	private:
		void OnWindowCloseEvent(Window* window, int exitCode);

	private:
		List<URef<Window>> windows;
		Array<PendingWindowsToCloseParams> pendingWindowsToClose;
		bool closeEngineAfterClosingAllWindows = true;
	};
}
